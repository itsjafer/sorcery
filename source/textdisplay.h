#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "ascii_graphics.h"
#include "observer.h"
#include <string>
#include <vector>
#include <memory>

class PlayerModel;
class NonPlayer;

typedef std::vector<card_template_t> row_template_r;
typedef std::pair<card_template_t, row_template_r> minion_template_m;

class TextDisplay: public Observer {
    int cardsPerRow = 5; // the number of cards we want displayed per row
    State currentCommand; // holds the enumeration of the current command
    int currentPlayer; // the player who issued the most recent command
    int minionIndex; // the minion that needs to be displayed

    // converts a NonPlayer object into a displayable card
    card_template_t cardTemplate(std::shared_ptr<NonPlayer> card);

    std::vector<row_template_r> minions; // holds the minion display cards
    std::vector<std::vector<row_template_r>> enchantments; // holds the players' minions' enchantments
    std::vector<row_template_r> players; // holds both players' row of player information
    std::vector<row_template_r> hands; // holds both players' hands
    
    // these functions update the display with information about the board
    void updatePlayers(std::vector<PlayerModel> boardInfos);
    void updateMinions(std::vector<PlayerModel> boardInfos);
    void updateHands(std::vector<PlayerModel> boardInfos);

    // these functions print out the board itself
    void printBoard(std::ostream &out) const;
    void printRow(row_template_r row, std::ostream &out, bool border = false) const;

    void printMessage(std::ostream &out, std::string &message) const;
    void printHelp(std::ostream &out) const; // prints the help message
    void printHand(std::ostream &out) const; // prints the hand
    void inspectMinion(std::ostream &out) const;  // prints the i'th minion
public: 
    TextDisplay();
    ~TextDisplay();
    void updateBoard(BoardController &whoNotified); 
    void notifyDisplay(BoardController &whoNotified, State command, int minionIndex) override;
    void notifyDisplay(std::string &message) override;
};

#endif
