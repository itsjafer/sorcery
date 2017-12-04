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
  string deck1File = "default.deck";
  string deck2File = "default.deck";
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
        deck1File = argv[i];
      }
      else if (arg == "-deck2") {
        // Same idea
        ++i;
        deck2File = argv[i];
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

  ifstream *deck1 = new ifstream{deck1File};
  ifstream *deck2 = new ifstream{deck2File};

  if (!(*deck1)) {
    cerr << "Unable to open " << deck1File << endl;
    return 1;
  }
  if (!(*deck2)) {
    cerr << "Unable to open " << deck2File << endl;
    return 1;
  }

  cout << "Main.cc: Found and opened decks" << endl;

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
    if (i == 0) deckFiles.emplace_back(unique_ptr<ifstream>(move(deck1)));
    else if (i == 1) deckFiles.emplace_back(unique_ptr<ifstream>(move(deck2)));
  }
  deck1 = nullptr;
  deck2 = nullptr;

  // our vector of displays
  vector<shared_ptr<Observer>> displays;
  shared_ptr<TextDisplay> td(new TextDisplay);
  shared_ptr<GraphicsDisplay> gd(new GraphicsDisplay(750));

  displays.emplace_back(td);
  displays.emplace_back(gd);
  
  cout << "main.cc: Board is now going to be initialized." << endl;
  // initialize the board
  BoardController board(names, deckFiles, displays, TestingMode);
  if (init.good()) board.setInit(&init);

  while (!board.gameEnded()) {

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
  cout << "Player " << board.whoWon() << " wins!" << endl;
}
