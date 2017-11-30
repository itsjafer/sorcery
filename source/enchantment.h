#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "nonplayer.h"

class Enchantment: public NonPlayer {
public:
    Enchantment(std::string &name, int cost, int owner, std::string &description): NonPlayer{name, cost, owner, description} {type = Type::Enchantment;}
    virtual ~Enchantment() = 0;
};

class AddEnchant: public Enchantment {
    int attMod;
    int defMod;
    int actPerTurn;
    int AbilityCost;
    bool silence;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    AddEnchant(std::string &cardName, int cardCost, int owner, std::string &description, int attMod, int defMod, int actPerTurn, int AbilityCost, int silencer);
};

#endif
