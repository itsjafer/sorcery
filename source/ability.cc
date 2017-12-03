#include "ability.h"

using namespace std;

Ability::Ability(std::string &name, int cost, int owner, string &description, Minion *minion):
        NonPlayer(name, cost, owner, description), minion(minion) {}
