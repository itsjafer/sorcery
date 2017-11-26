#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "nonplayer.h"

class Echantment: public NonPlayer {
public:
    void uncastCard();
    virtual ~Echantment() = 0;
};

#endif
