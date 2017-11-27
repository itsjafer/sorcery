#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "nonplayer.h"

class Enchantment: public NonPlayer {
public:
    void uncastCard();
    virtual ~Echantment() = 0;
};

public AddEnchant: public Enchantment {

};

#endif
