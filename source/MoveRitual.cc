#include "ritual.h"

using namespace std;

MoveRitual::MoveRitual(string &cardName, int cost, int owner, int charges, int activationCost, Event trigger,
                       string &target, string &destination, string &&description):
NonPlayer(cardName, cost, owner, description), Ritual(charges, activationCost, trigger), target(target), destination(destination){}