#include "spell.h"
#include "ritual.h"


using namespace std;

AddRitualSpell::AddRitualSpell(string &cardName, int cost, int owner, string &description, int chargeMod,
                               int costMod):
Spell(cardName, cost, owner, description), chargeMod(chargeMod), costMod(costMod){}

void AddRitualSpell::updateState(vector<Event> &events) {

}

void AddRitualSpell::castCard() {
  board->players.at(this->getOwner())->getRitual().setCharges(board->players.at(this->getOwner())->getRitual().getCharges() + chargeMod);
  board->players.at(this->getOwner())->getRitual().setActCost(board->players.at(this->getOwner())->getRitual().getActCost() + costMod);

}

void AddRitualSpell::castCard(int p, int t) {

}
