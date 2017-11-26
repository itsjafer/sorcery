#ifndef SPELL_H
#define SPELL_H

#include "nonplayer.h"

class Spell: public NonPlayer {
public:
    virtual ~Spell() = 0;
};

#endif
