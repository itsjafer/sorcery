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
    notifyObservers("Player " + std::to_string(currentPlayer + 1) + ", it is now your turn.");    
    return;
  }
  currentPlayer++;
  notifyObservers("Player " + std::to_string(currentPlayer + 1) + ", it is now your turn.");
}

void BoardController::attach(std::shared_ptr<Observer> o) {
  observers.push_back(o);
}

void BoardController::setInit(std::ifstream *init) {
  this->init = init;
}

void BoardController::notifyObservers(State command, int minion) {
  for (unsigned int i = 0; i < observers.size(); i++) {
    observers[i]->notify(*this, command, minion);
  }
}

void BoardController::notifyObservers(std::string message) {
  for (unsigned int i = 0; i < observers.size(); i++) {
    observers[i]->notify(message);
  }
}

BoardController::BoardController(std::vector<std::string> &players, std::vector<std::unique_ptr<std::ifstream>> &data, std::vector<std::shared_ptr<Observer>> &displays, bool testingMode) : 
boardData(players, data, testingMode), observers(displays), currentPlayer(0), gameOver(false) 
{

  // set the BoardModel to be a subject of our textdisplay
  //this->observers = displays;

  // checking if default.deck is still open
  if (!data[0]) {
    notifyObservers("BoardController.cc: default.deck was not found");
  }

  // have each of the players draw 3 cards
  for (unsigned int i = 0; i < players.size(); ++i) {
    boardData.players[i]->drawCard(4);
  }

  notifyObservers("Player " + std::to_string(currentPlayer + 1) + ", it is now your turn.");
}

void BoardController::attack(std::stringstream &ss) {
  // important note: i and j are in the domain [1,5], where 1 is the leftmost minion
  // j = 0 is the special case where the i'th minion attacks the inactive player himself
  int i;
  if (!(ss >> i)) throw std::invalid_argument("Invalid use of attack! Type 'help' for more info."); // i'th minion
  int j = (currentPlayer == 0) ? 2 : 1;

  if (ss.good()) {
    if (!(ss >> j)) throw std::invalid_argument("Invalid use of attack! Type 'help' for more info."); // i'th minion
  }

  // call the attack
  boardData.players[currentPlayer]->attack(i, j - 1);
}

void BoardController::play(std::stringstream &ss) {
  int i;
  int p;
  char t;

  if (!(ss >> i)) throw std::invalid_argument("Invalid use of play! Type 'help' for more info.");  // i'th card

  if (ss.good()) { // the p'th playercurrentPlayer
    if (!(ss >> p)) throw std::invalid_argument("Invalid use of play! Type 'help' for more info.");
    // TODO: discuss the next line..
    if (!(ss >> t)) throw std::invalid_argument("Invalid use of play! Type 'help' for more info."); // the t'th minion to affect

    int target;
    if (t == 'r')
      target = -1;
    else if (t >= '1' && t <= '5') {
      target = t - '0';
    }
    else throw std::invalid_argument("Invalid use of play! Type 'help' for more info.");

    // call the play
    boardData.players[currentPlayer]->play(i, p - 1, target);
  }
  else {
    // call the play
    boardData.players[currentPlayer]->play(i);
  }
}

void BoardController::use(std::stringstream &ss) {
  // important note: i and j are in the domain [1,5], where 1 is the leftmost minion
  // j = 0 is the special case where the i'th minion attacks the inactive player himself
  int i;
  int p;
  char t;

  if (!(ss >> i)) throw std::invalid_argument("Invalid use! Type 'help' for more info."); // i'th minion to use

  if (ss.good()) { // the p'th player
    if (!(ss >> p)) throw std::invalid_argument("Invalid use! Type 'help' for more info.");
    // TODO: discuss the next line..
    if (!(ss >> t)) throw std::invalid_argument("Invalid use! Type 'help' for more info."); // the t'th minion to affect

    int target;
    if (t == 'r')
      target = -1;
    else if (t >= '1' && t <= '5') {
      target = t - '0';
    }
    else throw std::invalid_argument("Invalid use of play! Type 'help' for more info.");

    // call the use
    boardData.players[currentPlayer]->use(i, p - 1, target);
  }
  else {

    // call the use
    boardData.players[currentPlayer]->use(i);
  }
}

void BoardController::discard(std::stringstream &ss) {
  int i;

  if (!(ss >> i)) throw std::invalid_argument("Invalid use of discard!");

  boardData.players[currentPlayer]->discard(i);
}

void BoardController::draw() {
  boardData.players[currentPlayer]->drawCard();
}

void BoardController::preTurn() {
  // increase the magic by 1
  int currentMagic = boardData.getMagic(currentPlayer);
  boardData.setMagic(currentPlayer, currentMagic + 1);


  // draw a card (if deck is non empty)
  // check if the deck is non-empty
  if (!boardData.isDeckEmpty(currentPlayer) && boardData.players[currentPlayer]->getHand().size() < 5) {
    // draw a card
    draw();

    // check for start-of-turn effects:
    // gonna create a vector for consistency-sake
    std::vector<Event> events;
    std::vector<Event> personalEvents;
    events.emplace_back(Event::startTurn);
    personalEvents.emplace_back(Event::thisStartTurn);
    try {
      boardData.updateBoard(personalEvents, currentPlayer);
      boardData.updateBoard(events);
    }
    catch(const InvalidMoveException &e) {
      notifyObservers("Player " + std::to_string(currentPlayer + 1) + ": " + e.what());
    }

  }
}

void BoardController::execute() {
  // this is the full command line
  std::string cmd;
  while ((init && getline(*init, cmd)) || getline(std::cin, cmd)) {
    std::string s;
    std::stringstream ss(cmd);
    ss >> s;
    try {
      if (s == "end") {
        // ends the current player's turn
        break;
      } else if (s == "quit") {
          gameOver = true;
          break;
      } else if (s == "attack") {
          attack(ss);
      } else if (s == "play") {
          play(ss);
      } else if (s == "use") {
          use(ss);
      } else if (s == "discard" && boardData.testingMode) {
          discard(ss);
      } else if (s == "draw" && boardData.testingMode) {
          draw();
      } else if (s == "inspect") {
          int i;
          if (ss >> i) notifyObservers(State::printMinion, i - 1); // the i'th minion to inspect
          else throw std::invalid_argument("Invalid inspect! Type 'help' for more info.");
      } else if (s == "hand") {
          notifyObservers(State::printHand);
      } else if (s == "board") {
          notifyObservers(State::printBoard);
      } else if (s == "help") {
          notifyObservers(State::printHelp);
      } else {
          throw std::invalid_argument("Invalid command! Type 'help' for more info.");
      }
    }
    catch(const std::out_of_range &e) {
      std::string message = "The card you are trying to access or perform an action on does not exist!";
      notifyObservers(message);
    }
    catch(const std::invalid_argument &e) {
      notifyObservers(e.what());
    }
    catch(const InvalidMoveException &e) {
      notifyObservers("Player " + std::to_string(currentPlayer + 1) + ": " + e.what());
    }
  }

}

void BoardController::postTurn() {

  // check for end-of-turn effects:
  // gonna create a vector for consistency-sake
  std::vector<Event> events;
  std::vector<Event> personalEvents;
  events.emplace_back(Event::endTurn);
  personalEvents.emplace_back(Event::thisEndTurn);
  try {
    boardData.updateBoard(personalEvents, currentPlayer);
    boardData.updateBoard(events);
  }
  catch(const InvalidMoveException &e) {
    notifyObservers(e.what());
  }

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
  int currentHealth = boardData.getHealth(0);
  for (unsigned int i = 0; i < boardData.players.size(); ++i) {
    if (boardData.getHealth(i) > currentHealth) {
      winner = i;
    } else
    {
      winner = -1;
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
