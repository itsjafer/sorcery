#ifndef TRIGGERED_H
#define TRIGGERED_H

#include "ability.h"

class Triggered: public Ability {
    Event trigger;
public:
    Triggered(Event trigger);
    virtual ~Triggered() = 0;
};

#endif
