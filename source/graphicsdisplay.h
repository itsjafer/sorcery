#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "observer.h"
#include "window.h"
#include <vector>
#include <memory>

class PlayerModel;
class NonPlayer;
class GraphicsDisplay: public Observer {
    const int winSize = 750;
    int cardWidth;
    int cardHeight;
    int logoHeight;
    int spacing;
    Xwindow xw;
    
    int cardsPerRow = 5; // the number of cards we want displayed per row
    State currentCommand; // holds the enumeration of the current command
    int currentPlayer; // the player who issued the most recent command
    int minionIndex; // the minion that needs to be displayed

    void displayPlayers(std::vector<PlayerModel> boardInfos);
    void displayMinions(std::vector<PlayerModel> boardInfos);
    void displayDescription(std::string, int x, int y);
    void displayCard(std::shared_ptr<NonPlayer> card, int x, int y);

    void displayHelp(); // prints the help message
    void displayHand(std::vector<PlayerModel> boardInfos); // prints the hand
    void inspectMinion(std::vector<PlayerModel> boardInfos);  // prints the i'th minion
public: 
    GraphicsDisplay(int winSize);
    ~GraphicsDisplay();
    void notifyDisplay(BoardController &whoNotified, State command, int minionIndex) override;
    void notifyDisplay(std::string &message) override;
};

#endif
