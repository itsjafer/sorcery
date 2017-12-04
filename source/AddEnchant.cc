#include "enchantment.h"
#include "ability.h"
#include <iostream>

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

void AddEnchant::unCast() {

}

void AddEnchant::unCast(int p, int t) {

  vector<Event> EventsForTarget;
  int target = t;

  if (defOperation == "+" ) {
    board->players.at(p)->minion(target).def -= defMod;
  } else if (defOperation == "-") {
    board->players.at(p)->minion(target).def += defMod;
  } else if (defOperation == "*" && defMod != 0) {
    board->players.at(p)->minion(target).def /= defMod;
  }

  if (attOperation == "+" ) {
    board->players.at(p)->minion(target).att -= attMod;
  } else if (attOperation == "-") {
    board->players.at(p)->minion(target).att += attMod;
  } else if (attOperation == "*" && attMod != 0) {
    board->players.at(p)->minion(target).att /= attMod;
  }

  board->players.at(p)->minion(target).actionPerTurn -= actPerTurn;

  if (board->players.at(p)->minion(target).abilities.back()->getType() == Type::ActivatedAbility) {
    board->players.at(p)->minion(target).abilities.back()->setCost(board->players.at(p)->minion(target).abilities.back()->getCost() - AbilityCost);
  }

  if (silence) {
    board->players.at(p)->minion(target).canCast = true;
  }

  if (board->players.at(p)->minion(target).def <= 0) {
    EventsForTarget.emplace_back(Event::minionDied);
    board->players.at(p)->minion(target).update(EventsForTarget);
    board->players.at(p)->toGrave(false, target - 1);
  }

}

void AddEnchant::castCard(int p, int t) {

  int target = t;

  if (defOperation == "+" ) {
    board->players.at(p)->minion(target).def += defMod;
  } else if (defOperation == "-") {
    board->players.at(p)->minion(target).def -= defMod;
  } else if (defOperation == "*") {
    board->players.at(p)->minion(target).def *= defMod;
  } else if (defOperation == "=") {
    board->players.at(p)->minion(target).def = defMod;
  }

  if (attOperation == "+" ) {
    board->players.at(p)->minion(target).att += attMod;
  } else if (attOperation == "-") {
    board->players.at(p)->minion(target).att -= attMod;
  } else if (attOperation == "*") {
    board->players.at(p)->minion(target).att *= attMod;
  } else if (attOperation == "=") {
    board->players.at(p)->minion(target).att = attMod;
  }

  board->players.at(p)->minion(target).actionPerTurn += actPerTurn;

  if (board->players.at(p)->minion(target).abilities.size() > 0 && board->players.at(p)->minion(target).abilities.back()->getType() == Type::ActivatedAbility) {
    board->players.at(p)->minion(target).abilities.back()->setCost(board->players.at(p)->minion(target).abilities.back()->getCost() + AbilityCost);
  }

  if (silence) {
    board->players.at(p)->minion(target).canCast = false;
  }


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
