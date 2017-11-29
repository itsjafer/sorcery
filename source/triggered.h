#ifndef TRIGGERED_H
#define TRIGGERED_H

#include "ability.h"

class Triggered: public Ability {
    Event trigger;
public:
    Triggered(Event trigger);
    virtual ~Triggered() = 0;
};

class AdderTriggered: public Triggered {
    int attMod;
    int defMod;
    std::string target;
public:
    AdderTriggered(Event trigger, int attMod, int defMod, std::string target, std::string description);
};

#endif
