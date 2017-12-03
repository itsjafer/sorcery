#include "graphicsdisplay.h"
#include "boardcontroller.h"
#include "playermodel.h"
#include <iostream>

// constructor
GraphicsDisplay::GraphicsDisplay(int winSize) : winSize(winSize), xw(winSize * 2, winSize) {
  // initialize the graphicsDisplay

  // set the card sizes
  cardWidth = winSize / 3;
  logoHeight = winSize / 4;
  cardHeight = (winSize - logoHeight) / 4;
  // start by creating an empty display with just templates
  std::cout << "graphicsdisplay.cc: Initializing graphicsdisplay." << std::endl;
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() {
 
}

void GraphicsDisplay::notifyDisplay(BoardController &whoNotified, State command, int minionIndex) {
  
  currentPlayer = whoNotified.getCurrentPlayer();
  std::cout << "graphicsdisplay.cc: I have been notified by player " << currentPlayer << "." << std::endl;

  // update the board when I'm notified
  this->minionIndex = minionIndex;

  std::cout << "graphicsdisplay.cc: Updating myself with players information." << std::endl;
  std::vector<PlayerModel> boardInfos = whoNotified.getPlayerInfos();

  displayPlayers(boardInfos);

}



void GraphicsDisplay::displayPlayers(std::vector<PlayerModel> boardInfos) {

  int halfway = (winSize - logoHeight) / 2;

  // draw the ritual
  xw.fillRectangle(0, 0, cardWidth, cardHeight, Xwindow::Black);
  xw.showAvailableFonts();
  xw.drawBigString(0, 0, "Ritual: ", Xwindow::Black);
  
  /*
  for (int i = 0; halfway; i += cardHeight) {
    for (int j = 0; j < winSize * 2; j += cardWidth) {
      // draw the ritual
      xw.fillRectangle(j, i, cardWidth, cardHeight, Xwindow::Black);
    }
  }*/
  



}