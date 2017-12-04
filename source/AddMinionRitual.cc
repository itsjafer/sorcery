#include "ritual.h"
#include "minion.h"

using namespace std;

AddMinionRitual::AddMinionRitual(string &cardName, int cost, int owner, string &description, int charges, int activationCost,
                                 int attMod, int defMod, int actPerTurn, int abilityCost, int silencer, Event trigger,
                                 string &target):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), attMod(attMod), defMod(defMod), actPerTurn(actPerTurn), abilityCost(abilityCost), target(target){
    if (silencer == 0) {
        silence = false;
    } else {
        silence = true;
    }
}

void AddMinionRitual::updateState(vector<Event> &events) {
  for (int i = 0; i < events.size(); i++) {
    if (events[i] == this->getTrigger()){
        castCard();
    }
  }
}

void AddMinionRitual::castCard() {
  if (board->getMagic(this->getOwner()) < this->getActCost() && !(board->testingMode)) throw InvalidMoveException(InvalidMove::InsufficientMagicRitual);
  if (this->getCharges() < 0) throw InvalidMoveException(InvalidMove::NoChargesLeft);

  board->setMagic(this->getOwner(), board->getMagic(this->getOwner()) - this->getActCost());
  this->setCharges(this->getCharges() - 1);
  if (board->getMagic(this->getOwner()) < 0) board->setMagic(this->getOwner(), 0);

  //Apply affects to minion
  board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).att += attMod;
  board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).def += defMod;
}

void AddMinionRitual::castCard(int p, int t) {

}
