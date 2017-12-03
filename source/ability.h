#ifndef ABILITY_H
#define ABILITY_H

#include "nonplayer.h"
#include "playercontroller.h"
#include "minion.h"

class Ability: public NonPlayer {
protected:
  Minion *minion;
public:
    Ability(std::string &name, int cost, int owner, std::string &description, Minion *minion);
    virtual ~Ability() = default;
};

#endif
