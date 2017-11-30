#ifndef ABILITY_H
#define ABILITY_H

#include "nonplayer.h"

class Ability: public NonPlayer {
public:
    Ability(std::string &name, int cost, int owner, std::string &description);
    virtual ~Ability() = default;
};

#endif
