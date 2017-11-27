#include "spell.h"

using namespace std;

AddSpell::AddSpell(std::string &cardName, int cost, int attMod, int defMod, int owner, std::string &Target,
                   std::string &&description):
        NonPlayer(cardName, cost, owner), attMod(attMod), defMod(defMod), Target(Target) {}