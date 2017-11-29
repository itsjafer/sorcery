#include "ritual.h"

using namespace std;

AddPlayerRitual::AddPlayerRitual(string &cardName, int cost, int owner, int charges, int activationCost, int healthMod, int magicMod,
                                 Event trigger, string &target, string &&description):
NonPlayer(cardName, cost, owner, description), Ritual(charges, activationCost, trigger), healthMod(healthMod), magicMod(magicMod) {}