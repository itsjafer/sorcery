#include "boardcontroller.h"
#include "boardmodel.h"
#include "textdisplay.h"
#include "event.h"
#include <stdexcept>
#include "playercontroller.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "playermodel.h"

void BoardController::switchPlayers() {
  if (currentPlayer == boardData.players.size() - 1) {
    currentPlayer = 0;
    return;
  }
  currentPlayer++;
}

void BoardController::attach(std::shared_ptr<Observer> o) {
  observers.push_back(o);
}

void BoardController::notifyObservers(State command, int minion) {
  //std::cout << "There are " << observers.size() << " observers" << std::endl;
  for (unsigned int i = 0; i < observers.size(); i++) {
    std::cout << i << std::endl;
    observers[i]->notify(*this, command, minion);
  }
}

BoardController::BoardController(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data, std::vector<std::shared_ptr<Observer>> &displays, bool testingMode) : 
boardData(players, data, testingMode), currentPlayer(0), gameOver(false) 
{

  // set the BoardModel to be a subject of our textdisplay
  this->observers = displays;
  //std::cout << "BoardController.cc: I have been given " << observers.size() << " observers!" << std::endl;

  // checking if default.deck is still open
  if (!data[0]) {
    std::cout << "BoardController.cc: default.deck was not found" << std::endl;
  }

  // have each of the players draw 3 cards
  for (unsigned int i = 0; i < players.size(); ++i) {
    //std::cout << "BoardController.cc: Player " << i << " is drawing 3 cards" << std::endl;
    boardData.players[i]->drawCard(4);
    //std::cout << "BoardController.cc: Player " << i << " now has " << boardData.players[i]->getHand().size() << " cards in their hand." << std::endl;
  }
}

void BoardController::attack(std::stringstream &ss) {
  // important note: i and j are in the domain [1,5], where 1 is the leftmost minion
  // j = 0 is the special case where the i'th minion attacks the inactive player himself
  int i;
  if (!(ss >> i)) throw std::invalid_argument("Invalid use of attack! Type 'help' for more info."); // i'th minion
  int j = 0;

  if (ss.good()) {
    if (!(ss >> j)) throw std::invalid_argument("Invalid use of attack! Type 'help' for more info."); // i'th minion
  }

  std::cout << "BoardController.cc: Player " << currentPlayer << " has attacked using minion " << i << " on " << j << std::endl;          
  // call the attack
  boardData.players[currentPlayer]->attack(i, j);
}

void BoardController::play(std::stringstream &ss) {
  int i;
  int p;
  int t;

  if (!(ss >> i)) throw std::invalid_argument("Invalid use of play! Type 'help' for more info.");  // i'th card

  if (ss.good()) { // the p'th player
    if (!(ss >> p)) throw std::invalid_argument("Invalid use of play! Type 'help' for more info.");
    if (!(ss >> t)) throw std::invalid_argument("Invalid use of play! Type 'help' for more info."); // the t'th minion to affect
    std::cout << "BoardController.cc: Player " << currentPlayer << " has used card " << i << " on player " << p << "'s minion " << t << std::endl;                    
    // call the play
    boardData.players[currentPlayer]->play(i, p, t);
  }
  else {
    // call the play
    std::cout << "BoardController.cc: Player " << currentPlayer << " has used card " << i << std::endl;                          
    boardData.players[currentPlayer]->play(i);
  }
}

void BoardController::use(std::stringstream &ss) {
  // important note: i and j are in the domain [1,5], where 1 is the leftmost minion
  // j = 0 is the special case where the i'th minion attacks the inactive player himself
  int i;
  int p;
  int t;

  if (!(ss >> i)) throw std::invalid_argument("Invalid use! Type 'help' for more info."); // i'th minion to use

  if (ss.good()) { // the p'th player
    if (!(ss >> p)) throw std::invalid_argument("Invalid use! Type 'help' for more info.");
    if (!(ss >> t)) throw std::invalid_argument("Invalid use! Type 'help' for more info."); // the t'th minion to affect

    std::cout << "BoardController.cc: Player " << currentPlayer << " has used minion " << i << "'s ability on player " << p << "'s minion " << t << std::endl;                              
    // call the use
    boardData.players[currentPlayer]->use(i, p, t);
  }
  else {
    std::cout << "BoardController.cc: Player " << currentPlayer << " has used the ability of minion " << i << std::endl;                                  
    // call the use
    boardData.players[currentPlayer]->use(i);
  }
}

void BoardController::discard(std::stringstream &ss) {
  int i;

  if (!(ss >> i)) throw std::invalid_argument("Invalid use of discard!");

  std::cout << "BoardController.cc: Player " << currentPlayer << " has discarded card " << i << std::endl;
  boardData.players[currentPlayer]->discard(i);
}

void BoardController::draw() {
  boardData.players[currentPlayer]->drawCard();
}

void BoardController::preTurn() {
  std::cout << "BoardController.cc: preTurn starting now." << std::endl;
  // increase the magic by 1
  int currentMagic = boardData.getMagic(currentPlayer);
  boardData.setMagic(currentPlayer, currentMagic + 1);

  //std::cout << "BoardController.cc: Player " << currentPlayer << " magic increased by 1." << std::endl;
  //std::cout << "BoardController.cc: Player " << currentPlayer << " magic is now " << boardData.getMagic(currentPlayer) << std::endl;

  // draw a card (if deck is non empty)
  // check if the deck is non-empty
  if (!boardData.isDeckEmpty(currentPlayer) && boardData.players[currentPlayer]->getHand.size() < 5) {
    // draw a card
    boardData.players[currentPlayer]->drawCard();
    //std::cout << "BoardController.cc: Player " << currentPlayer << " has drawn a card." << std::endl;
    //std::cout << "BoardController.cc: Player " << currentPlayer << " now has " << boardData.players[currentPlayer]->getHand().size() << " cards in their hand." << std::endl;
  }

  // check for start-of-turn effects:
  // gonna create a vector for consistency-sake
  std::vector<Event> events {Event::startTurn};
  boardData.updateBoard(events);
  std::cout << "BoardController.cc: Checking for start of turn effects." << std::endl;

}

void BoardController::execute() {
  // this is the full command line
  std::string cmd;
  std::cout << "BoardController.cc: Listening for commands." << std::endl;
  while (getline(std::cin, cmd)) {
    std::string s;
    std::stringstream ss(cmd);
    ss >> s;
    if (s == "end") {
      std::cout << "BoardController.cc: Player " << currentPlayer << " has ended their turn." << std::endl;
      // ends the current player's turn
      break;
    } else if (s == "quit") {
        std::cout << "BoardController.cc: Player " << currentPlayer << " has ended the game." << std::endl;
        gameOver = true;
        break;
    } else if (s == "attack") {
        try {
          attack(ss);
        }
        catch(const std::out_of_range &e) {
          std::cout << "The minion you are trying to attack (or use to attack) does not exist!" << std::endl;
        }
        catch(const std::invalid_argument &e) {
          std::cout << e.what() << std::endl;
        }
    } else if (s == "play") {
        try {
          play(ss);
        }
        catch(const std::out_of_range &e) {
          std::cout << "The card you are trying to play does not exist!" << std::endl;
        }
        catch(const InvalidMoveException &e) {
          std::cout << e.what() << std::endl;
        }
        catch(const std::invalid_argument &e) {
          std::cout << e.what() << std::endl;
        }
    } else if (s == "use") {
        try {
          use(ss);
        }
        catch(const std::out_of_range &e) {
          std::cout << "The card you are trying to use (or use on) does not exist!" << std::endl;
        }
        catch(const InvalidMoveException &e) {
          std::cout << e.what() << std::endl;
        }
        catch(const std::invalid_argument &e) {
          std::cout << e.what() << std::endl;
        }
    } else if (s == "discard" && boardData.testingMode) {
      std::cout << "discard: TestingMode works!" << std::endl;
      try {
        discard(ss);
      }
      catch(const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
      }
      catch(const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (s == "draw" && boardData.testingMode) {
      std::cout << "draw: TestingMode works!" << std::endl;
      try {
        draw();
      }
      catch(const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (s == "inspect") {
      int i;
      if (ss >> i) notifyObservers(State::printMinion, i); // the i'th minion to inspect
      else std::cout << "Improper usage of inspect! Type help for more info." << std::endl;
    } else if (s == "hand") {
      notifyObservers(State::printHand);
    } else if (s == "board") {
      notifyObservers(State::printBoard);
    } else if (cmd == "help") {
      notifyObservers(State::printHelp);
    } else {
      std::cout << "Invalid command!" << std::endl;
    } 
  }

}

void BoardController::postTurn() {

  std::cout << "BoardController.cc: Checking for end of turn effects." << std::endl;
  // check for end-of-turn effects:
  // gonna create a vector for consistency-sake
  std::vector<Event> events;
  std::vector<Event> personalEvents;
  events.emplace_back(Event::endTurn);
  personalEvents.emplace_back(Event::thisEndTurn);
  boardData.updateBoard(events);
  boardData.updateBoard(personalEvents, currentPlayer);

  // check if anyone is dead
  for (unsigned int i = 0; i < boardData.players.size(); ++i) {
    if (boardData.getHealth(i) <= 0) {
      gameOver = true;
      break;
    }
  }
}
bool BoardController::gameEnded() {
  return gameOver;
}

int BoardController::whoWon() {
  int winner = 0; // the default winner
  for (unsigned int i = 0; i < boardData.players.size(); ++i) {
    if (boardData.getHealth(i) < boardData.getHealth(winner)) {
      winner = i;
    }
  }
  return winner;
}

BoardController::~BoardController() {
  // is this real life, or is this just fantasy?
}

std::vector<PlayerModel> BoardController::getPlayerInfos() const {
  std::vector<PlayerModel> playerInfos;
  for (unsigned int i = 0; i < boardData.players.size(); ++i) {
    PlayerModel myInfo = boardData.players[i]->getPlayerData();
    playerInfos.emplace_back(myInfo);
  }
  return playerInfos;
}

int BoardController::getCurrentPlayer() {
  return currentPlayer;
}
