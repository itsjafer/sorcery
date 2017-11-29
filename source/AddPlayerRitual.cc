#include "ritual.h"

using namespace std;

AddPlayerRitual::AddPlayerRitual(string &cardName, int cost, int owner, int charges, int activationCost, int healthMod, int magicMod,
                                 Event trigger, string &target, string &&description):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), healthMod(healthMod), magicMod(magicMod) {}