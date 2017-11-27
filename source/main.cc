#include "subject.h"
#include "observer.h"
#include "boardcontroller.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {

  // initialize each player
  int numPlayers = 2;
  vector<string> names; // this vector is a list of names (used for player construction)
  vector<unique_ptr<ifstream>> deckFiles;

  for (int i = 0; i < numPlayers; ++i) {
    // get the names for each player
    string name;
    cout << "Player " << i << ", what is your name?" << endl;
    getline(cin, name);
    names.emplace_back(name);

    // get the deckfiles for each player
    // for now, we're going to assume both players use default.deck
    unique_ptr<ifstream> deckFile(new ifstream("default.deck"));
    deckFiles.emplace_back(move(deckFile));
  }

  // initialize the board  
  BoardController board(names, deckFiles);

  while (!board.gameEnded()) {
    // go through the three stages of turns
    board.preTurn();
    board.execute();
    board.postTurn();
  }
  
  // find out who won
  cout << "Player " << board.whoWon() << " wins!" << endl;
}
