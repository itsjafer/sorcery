#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "nonplayer.h"

class Enchantment: public NonPlayer {
public:
    Enchantment(std::string &name, int cost, int owner, std::string &&description = "");
    virtual ~Enchantment() = 0;
};

class AddEnchant: public Enchantment {
    int attMod;
    int defMod;
    int actPerTurn;
    int AbilityCost;
    bool silence;
    void castCard() override;
public:
    AddEnchant(std::string &cardName, int cardCost, int owner, int attMod, int defMod, int actPerTurn, int AbilityCost, int silencer, std::string &&description);
};

#endif
