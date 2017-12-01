#include "enchantment.h"

using namespace std;

AddEnchant::AddEnchant(std::string &cardName, int cardCost, int owner, std::string &description, int attMod, int defMod, int actPerTurn,
                       int AbilityCost, std::string attFier, std::string defFier, int silencer):
        Enchantment(cardName, cardCost, owner, description), attMod(attMod), defMod(defMod), actPerTurn(actPerTurn), AbilityCost(AbilityCost), attFier(attFier), defFier(defFier)
{
    if (silencer == 0) {
        this->silence = false;
    } else {
        this->silence = true;
    }
}

void AddEnchant::updateState(vector<Event> &events) {

}

void AddEnchant::castCard() {

}

void AddEnchant::castCard(int p, char t) {

}
