#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include "ascii_graphics.h"
#include <string>
#include <vector>

class TextDisplay: public Observer {
    std::vector<std::vector<card_template_t>> theDisplay; // holds all display information
    std::vector<card_template_t> playerOneField;
    std::vector<card_template_t> playerOneHand;
    std::vector<card_template_t> playerTwoField;
    std::vector<card_template_t> playerTwoHand;

public: 
    TextDisplay();
    ~TextDisplay();

    void notifyDisplay(Subject &whoNotified) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
