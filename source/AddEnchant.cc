#include "enchantment.h"

using namespace std;

AddEnchant::AddEnchant(std::string &cardName, int cardCost, int owner, std::string &description, int attMod, int defMod, int actPerTurn,
                       int AbilityCost, std::string &attOperation, std::string &defOperation, int silencer):
        Enchantment(cardName, cardCost, owner, description), attMod(attMod), defMod(defMod), actPerTurn(actPerTurn), AbilityCost(AbilityCost), attOperation(attOperation), defOperation(defOperation)
{
    type = Type::AddEnchantment;
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

int AddEnchant::getAttackModifier() {
    return attMod;
}

int AddEnchant::getDefenceModifier() {
    return defMod;
}

std::string &AddEnchant::getAttackOperator() {
    return attOperation;
}

std::string &AddEnchant::getDefenceOperator() {
    return defOperation;
}