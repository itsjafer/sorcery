#ifndef RITUAL_H
#define RITUAL_H

#include "nonplayer.h"

class Ritual: public NonPlayer {
    int charges;
    int activationCost;
    Event trigger;
public:
    Ritual(int charges, int activationCost, Event trigger);
    virtual ~Ritual() = 0;
};

#endif
