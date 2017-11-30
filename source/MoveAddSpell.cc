#include "spell.h"

using namespace std;


MoveAddSpell::MoveAddSpell(string &cardName, int cost, int owner, string &description, int attMod, int defMod,
                           string &moveSource, string &moveDestination, string &Target):
        Spell(cardName, cost, owner, description), attMod(attMod), defMod(defMod), moveSource(moveSource), moveDestination(moveDestination), Target(Target){}