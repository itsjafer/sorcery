#include "observer.h"
#include "boardcontroller.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {

  bool TestingMode = false;
  bool GraphicsMode = false;
  ifstream init;

  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      string arg = argv[i];
      if (arg == "-testing") {
        TestingMode = true;
      }
      else if (arg == "-deck1") {
        // Next arg is filename of -deck1, set up deck1 to that filename
        ++i;
      }
      else if (arg == "-deck2") {
        // Same idea
        ++i;
      }
      else if (arg == "-init") {
        // Next arg is a filename--whatever commands are in this are the first commands to be used
        ++i;
        init.open(argv[i]);
        if (!init) {
          cerr << "Unable to open init file" << endl;
          return 1;
        }
      }
      else if (arg == "-graphics") {
        GraphicsMode = true;
      }
    }
  }

  // initialize each player
  int numPlayers = 2;
  vector<string> names; // this vector is a list of names (used for player construction)
  vector<unique_ptr<ifstream>> deckFiles;

  ifstream deck("default.deck");
  if (!deck) {
    cerr << "Unable to open default.deck" << endl;
    return 1;
  }

  cout << "Main.cc: Found and opened default.deck" << endl;

  for (int i = 0; i < numPlayers; ++i) {
    // get the names for each player
    string name;
    if (!(init >> name)) {
      cout << "Player " << i << ", what is your name?" << endl;
      getline(cin, name);
    }
    names.emplace_back(name);

    // get the deckfiles for each player
    // for now, we're going to assume both players use default.deck
    deckFiles.emplace_back(unique_ptr<ifstream>(new ifstream("default.deck")));
  }

  // our vector of displays
  vector<shared_ptr<Observer>> displays;
  displays.emplace_back(new TextDisplay);

  if (GraphicsMode == true) {
    displays.emplace_back(new GraphicsDisplay(750));
  }
  
  cout << "main.cc: Board is now going to be initialized." << endl;
  // initialize the board
  BoardController board(names, deckFiles, displays, TestingMode);
  if (init.good()) board.setInit(&init);

  while (!board.gameEnded() && !cin.eof()) {

    // go through the three stages of turns
    //cout << "main.cc: Board is now going to go through preTurn." << endl;
    board.preTurn();
    //cout << "main.cc: Board is now going to go through execute." << endl;
    board.execute();
    if (board.gameEnded()) return 0;
    //cout << "main.cc: Board is now going to go through postTurn." << endl;
    board.postTurn();

    // switch the player turn
    //cout << "main.cc: Board is now going to switch turns." << endl;
    board.switchPlayers();
  }

  // find out who won
  if (board.whoWon() < 0) {
    cout << "Tie game!" << endl;
  } else {
    cout << "Player " << board.whoWon() << " wins!" << endl;
  }
}
