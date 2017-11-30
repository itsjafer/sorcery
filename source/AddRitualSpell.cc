#include "spell.h"

using namespace std;

AddRitualSpell::AddRitualSpell(string &cardName, int cost, int owner, string &description, int chargeMod,
                               int costMod):
Spell(cardName, cost, owner, description), chargeMod(chargeMod), costMod(costMod){}

void AddRitualSpell::updateState(vector<Event> &events) {

}

void AddRitualSpell::castCard() {

}

void AddRitualSpell::castCard(int p, char t) {

}