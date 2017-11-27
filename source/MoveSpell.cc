#include "spell.h"

using namespace std;

MoveSpell::MoveSpell(string &cardName, int cost, int owner, string &moveSource, string &moveDestination, string &Target, string &&description) :
        NonPlayer(cardName, cost, owner), moveSource(moveSource), moveDestination(moveDestination), Target(Target) {}