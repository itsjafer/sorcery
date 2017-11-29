#include "spell.h"

using namespace std;

MoveSpell::MoveSpell(string &cardName, int cost, int owner, string &description, string &moveSource, string &moveDestination, string &Target) :
        Spell(cardName, cost, owner, description), moveSource(moveSource), moveDestination(moveDestination), Target(Target) {}