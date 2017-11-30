#include "activated.h"

using namespace std;

Activated::Activated(string &name, int cost, int owner, string &description): Ability{name, cost, owner, description} {
    type = Type::ActivatedAbility;
}
