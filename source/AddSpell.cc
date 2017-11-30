#include "spell.h"

using namespace std;

AddSpell::AddSpell(std::string &cardName, int cost, int owner, string &description, int attMod, int defMod, string attFier, string defFier, string &Target):
        Spell(cardName, cost, owner, description), attMod(attMod), defMod(defMod), attFier(attFier), defFier(defFier), Target(Target) {}

void AddSpell::updateState(vector<Event> &events) {

}

void AddSpell::castCard() {

}

void AddSpell::castCard(int p, char t) {

}
