#ifndef ABILITY_H
#define ABILITY_H

#include "nonplayer.h"

class Ability: public NonPlayer {
public:
    virtual ~Ability() = 0;
};

#endif
