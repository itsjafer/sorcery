#include "enchantment.h"

using namespace std;

AddEnchant::AddEnchant(std::string &cardName, int cardCost, int owner, std::string &description, int attMod, int defMod, int actPerTurn,
                       int AbilityCost, int silencer):
        Enchantment(cardName, cardCost, owner, description), attMod(attMod), defMod(defMod), actPerTurn(actPerTurn), AbilityCost(AbilityCost)
{
    if (silencer == 0) {
        this->silence = false;
    } else {
        this->silence = true;
    }
}