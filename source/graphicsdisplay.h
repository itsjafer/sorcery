#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "observer.h"
#include "window.h"
#include <vector>

class PlayerModel;
class GraphicsDisplay: public Observer {
    const int winSize = 500;
    int cardWidth;
    int cardHeight;
    int logoHeight;
    Xwindow xw;
    int cardsPerRow = 5; // the number of cards we want displayed per row
    State currentCommand; // holds the enumeration of the current command
    int currentPlayer; // the player who issued the most recent command
    int minionIndex; // the minion that needs to be displayed

public: 
    GraphicsDisplay(int winSize);
    ~GraphicsDisplay();
    void notifyDisplay(BoardController &whoNotified, State command, int minionIndex) override;
    void displayPlayers(std::vector<PlayerModel> boardInfos);
};

#endif