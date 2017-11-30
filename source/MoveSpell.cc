#include "spell.h"

using namespace std;

MoveSpell::MoveSpell(string &cardName, int cost, int owner, string &description, string &moveSource, string &moveDestination, string &Target) :
        Spell(cardName, cost, owner, description), moveSource(moveSource), moveDestination(moveDestination), Target(Target) {}

void MoveSpell::updateState(vector<Event> &events) {

}

void MoveSpell::castCard() {

}

void MoveSpell::castCard(int p, char t) {

}
