#include "boardcontroller.h"
#include "boardmodel.h"
#include "event.h"
#include <iostream>
#include <vector>

void BoardController::switchPlayers() {
  if (currentPlayer == boardData.players.size() - 1) {
    currentPlayer = 0;
  }
  currentPlayer++;
}

BoardController::BoardController(std::vector<std::string> players, std::vector<std::ifstream> &data) : boardData(players, data), currentPlayer(0), gameOver(false) {
}

void BoardController::preTurn() {
  // increase the magic by 1
  int currentMagic = boardData.getMagic(currentPlayer);
  boardData.setMagic(currentPlayer, currentMagic + 1);
  
  // draw a card (if deck is non empty)
  // check if the deck is non-empty
  if (!boardData.isDeckEmpty(currentPlayer)) {
    // draw a card
    boardData.players[currentPlayer].drawCard();
  }

  // check for start-of-turn effects:
  // gonna create a vector for consistency-sake
  std::vector<Event> events;
  events.emplace_back(Event::startTurn);
  boardData.updateBoard(events);
}

void BoardController::execute() {
  // this is the full command line
  std::string cmd;

  while (true) {
    if (cmd == "end") {
      // ends the current player's turn
      break;
    } else if (cmd == "quit") {
        gameOver = true;
    } else if (cmd == "attack") {
        // important note: i and j are in the domain [1,5], where 1 is the leftmost minion
        // j = 0 is the special case where the i'th minion attacks the inactive player himself
        int i;
        std::cin >> i; // i'th minion
        int j;

        if (!(std::cin >> j)) {
          j = 0; // if we're not given a j, we'll attack the player
        }

        // call the attack
        boardData.players[currentPlayer].attack(i, j);

    } else if (cmd == "play") {
        int i;
        int p;
        int t;

        std::cin >> i; // i'th card
  
        if ((std::cin >> p)) { // the p'th player
          std::cin >> t; // the t'th minion to affect

          // call the play
          boardData.players[currentPlayer].play(i, p, t);
          continue;
        }

        // call the play
        boardData.players[currentPlayer].play(i);
    } else if (cmd == "use") {
        // important note: i and j are in the domain [1,5], where 1 is the leftmost minion
        // j = 0 is the special case where the i'th minion attacks the inactive player himself
        int i;
        int p;
        int t;

        std::cin >> i; // i'th minion to use
  
        if ((std::cin >> p)) { // the p'th player
          std::cin >> t; // the t'th minion to affect

          // call the use
          boardData.players[currentPlayer].use(i, p, t);
          continue;
        }

        // call the use
        boardData.players[currentPlayer].use(i);
    } else if (cmd == "inspect") {
      // textDisplay
    } else if (cmd == "hand") {
      // textDisplay
    } else if (cmd == "board") {
      // textDisplay
    } else if (cmd == "help") {
      // textDisplay
    } else if (cmd == "draw") {
      // this is only available in testing mode
      boardData.players[currentPlayer].drawCard();
    } else if (cmd == "discard") {
      // this is only available in testing mode
      // TODO: ADD TO PLAYER.H
    } 
  }

}

void BoardController::postTurn() {

  // check for end-of-turn effects:
  // gonna create a vector for consistency-sake
  std::vector<Event> events;
  events.emplace_back(Event::endTurn);
  boardData.updateBoard(events);

  // check if anyone is dead
  for (int i = 0; i < boardData.players.size(); ++i) {
    if (boardData.getHealth(i) <= 0) {
      gameOver = true;
      break;
    }
  }

  // switch the player turn
  switchPlayers();
}
bool BoardController::gameEnded() {
  return gameOver;
}

int BoardController::whoWon() {
  int winner = 0; // the default winner
  for (int i = 0; i < boardData.players.size(); ++i) {
    if (boardData.getHealth(i) < boardData.getHealth(winner)) {
      winner = i;
    }
  }
  return winner;
}

BoardController::~BoardController() {
  // is this real life, or is this just fantasy?
}