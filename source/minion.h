#ifndef MINION_H
#define MINION_H

#include "nonplayer.h"
#include <memory>

class Ability;
class Enchantment;

class Minion: public NonPlayer {
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    int att;
    int def;
    int action = 0;
    bool canAttack = true;
    std::vector<std::shared_ptr<Ability>> abilities;
    std::vector<std::shared_ptr<Enchantment>> enchantments;

    Minion(std::string &name, int cost, int owner, int attack, int defence, std::vector<std::ifstream> &abilities);
    void attack(int i = 0, int me = 0);
    ~Minion();
};

#endif
