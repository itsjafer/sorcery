#include "activated.h"

using namespace std;

Activated::Activated(string &name, int cost, int owner, string &description, Minion *minion): Ability{name, cost, owner, description, minion} {
    type = Type::ActivatedAbility;
}
