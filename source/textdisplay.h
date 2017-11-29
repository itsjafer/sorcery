#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include "ascii_graphics.h"
#include <string>
#include <vector>

class TextDisplay: public Observer {
    std::vector<std::vector<card_template_t>> fields;
    std::vector<std::vector<card_template_t>> hands;
    void printHand(int currentPlayer, std::ostream &out, const TextDisplay &td) const;
    void printField(int currentPlayer, std::ostream &out, const TextDisplay &td) const;
    
public: 
    TextDisplay();
    ~TextDisplay();
    void printBoard(Subject &whoNotified); 
    void notifyDisplay(Subject &whoNotified, State command) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    friend std::ostream &operator<<(std::ostream &out, const int i);

};

#endif
