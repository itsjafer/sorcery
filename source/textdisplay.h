#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"

class TextDisplay: public Observer {
    void notifyDisplay(Subject &whoNotified);
public: 
    TextDisplay();
    ~TextDisplay();
};

#endif
