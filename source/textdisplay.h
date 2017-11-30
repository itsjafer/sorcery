#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include "ascii_graphics.h"
#include <string>
#include <vector>

class TextDisplay: public Observer {
    State currentCommand; // holds the enumeration of the current command
    std::vector<std::vector<card_template_t>> minionRow; // holds both players' row of minions
    std::vector<std::vector<card_template_t>> playerRow; // holds both players' row of player information
    std::vector<std::vector<card_template_t>> hands; // holds both players' hands
    
    void update(Subject &whoNotified); // updates the board with information from whoever notified me
    void printBoard(std::ostream &out) const; // prints the whole board to an ostream
    void printMinionRow(int currentPlayer, std::ostream &out) const;
    void printPlayerRow(int currentPlayer, std::ostream &out) const;
    void printMinion(std::ostream &out) const;
    void printHelp(std::ostream &out) const;
    void printHand(std::ostream &out) const;    
public: 
    TextDisplay();
    ~TextDisplay();
    void updateBoard(Subject &whoNotified); 
    void notifyDisplay(Subject &whoNotified, State command, int minion = 0) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

};

#endif
