#ifndef MINION_H
#define MINION_H

#include "nonplayer.h"

class Ability;
class Enchantment;

class Minion: public NonPlayer {
public:
    int att;
    int def;
    int action = 0;
    std::vector<Ability> abilities;
    std::vector<Enchantment *> enchantments;

    Minion(std::string &name, int cost, int owner, int attack, int defence, std::vector<std::ifstream> &abilities);
    void attack(int i = 0);
    virtual ~Minion() = 0;
};

#endif
