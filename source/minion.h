#ifndef MINION_H
#define MINION_H

#include "nonplayer.h"
#include <memory>

class Ability;
class Enchantment;

class Minion: public NonPlayer {
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    int att;
    int def;
    int actionPerTurn = 1;
    int action = 0;
    bool canCast = true;
    std::vector<std::shared_ptr<Ability>> abilities;
    std::vector<std::shared_ptr<Enchantment>> enchantments;

    Minion(std::string &name, int cost, int owner, int attack, int defence, std::vector<std::ifstream> &abilities);
    void attack(int i = 0, int me = 0);
    int getAttack();
    int getDefence();
    int getAbilityCost(int i = 0);
    bool hasAbility();
    Type getAbilityType(int i = 0);
    ~Minion();
};

#endif
