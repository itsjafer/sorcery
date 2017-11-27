#include "ability.h"

using namespace std;

Ability::Ability(std::string &name, int cost, int owner, string &&description):
        NonPlayer(name, cost, owner, description) {}