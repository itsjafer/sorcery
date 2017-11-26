#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "observer.h"

class GraphicsDisplay: public Observer {
    void notifyDisplay(Subject &whoNotified);
public: 
    GraphicsDisplay();
    ~GraphicsDisplay();
};

#endif