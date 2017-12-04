#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "nonplayer.h"
#include "minion.h"
#include "playercontroller.h"

class Enchantment: public NonPlayer {
public:
    Enchantment(std::string &name, int cost, int owner, std::string &description): NonPlayer{name, cost, owner, description} {}
    virtual ~Enchantment() = default;
    virtual void unCast() = 0;
    virtual void unCast(int p, int t = -1) = 0;
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
    void unCast() override;
    void castCard(int p, int t = -1) override;
    void unCast(int p, int t = -1) override;
public:
    AddEnchant(std::string &cardName, int cardCost, int owner, std::string &description, int attMod, int defMod, int actPerTurn, int AbilityCost, std::string &attOperation, std::string &defOperation, int silencer);
    int getAttackModifier();
    int getDefenceModifier();
    std::string &getAttackOperator();
    std::string &getDefenceOperator();
    ~AddEnchant() { }
};

#endif
