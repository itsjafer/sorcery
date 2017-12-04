#include "ritual.h"
#include <iostream>

using namespace std;

AddPlayerRitual::AddPlayerRitual(string &cardName, int cost, int owner, string &description, int charges, int activationCost, int healthMod, int magicMod,
                                 Event trigger, string &target):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), healthMod(healthMod), magicMod(magicMod) {}

void AddPlayerRitual::updateState(vector<Event> &events) {
  for (int i = 0; i < events.size(); i++) {
    if (events[i] == this->getTrigger()){
        castCard();
    }
  }
}

void AddPlayerRitual::castCard() {
  if (board->getMagic(this->getOwner()) < this->getActCost() && !(board->testingMode)) throw InvalidMoveException(InvalidMove::InsufficientMagicRitual);
  if (this->getCharges() < 0) throw InvalidMoveException(InvalidMove::NoChargesLeft);

  board->setMagic(this->getOwner(), board->getMagic(this->getOwner()) - this->getActCost());
  if (board->getMagic(this->getOwner()) < 0) board->setMagic(this->getOwner(), 0);
  this->setCharges(this->getCharges() - 1);
  board->setHealth(this->getOwner(), board->getHealth(this->getOwner()) + healthMod);
  board->setMagic(this->getOwner(), board->getMagic(this->getOwner()) + magicMod);
}

void AddPlayerRitual::castCard(int p, int t) {

}
