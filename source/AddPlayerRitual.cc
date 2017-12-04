#include "ritual.h"

using namespace std;

AddPlayerRitual::AddPlayerRitual(string &cardName, int cost, int owner, string &description, int charges, int activationCost, int healthMod, int magicMod,
                                 Event trigger, string &target):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), healthMod(healthMod), magicMod(magicMod) {}

void AddPlayerRitual::updateState(vector<Event> &events) {

}

void AddPlayerRitual::castCard() {

}

void AddPlayerRitual::castCard(int p, int t) {

}
