#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include <string>
#include <vector>

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
public: 
    TextDisplay();
    ~TextDisplay();

    void notifyDisplay(Subject &whoNotified) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
