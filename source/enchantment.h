#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "nonplayer.h"

class Enchantment: public NonPlayer {
public:
    Enchantment(std::string &name, int cost, int owner, std::string &description): NonPlayer{name, cost, owner, description} {}
    virtual ~Enchantment() = default;
};

class AddEnchant: public Enchantment {
    int attMod;
    int defMod;
    int actPerTurn;
    int AbilityCost;
    bool silence;
    std::string attOperation;
    std::string defOperation;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    AddEnchant(std::string &cardName, int cardCost, int owner, std::string &description, int attMod, int defMod, int actPerTurn, int AbilityCost, std::string attOperation, std::string defOperation, int silencer);
    int getAttackModifier();
    int getDefenceModifier();
    std::string &getAttackOperator();
    std::string &getDefenceOperator();
    ~AddEnchant() { }
};

#endif
