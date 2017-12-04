#include "ritual.h"

using namespace std;

MoveRitual::MoveRitual(string &cardName, int cost, int owner, string &description, int charges, int activationCost, Event trigger,
                       string &target, string &destination):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), target(target), destination(destination){}

void MoveRitual::updateState(vector<Event> &events) {
  //Go through list of given events
  for (int i = 0; i < events.size(); ++i) {
    //check the event and if it triggers this ability
    if (events[i] == this->getTrigger()) {
      this->castCard();
    }
  }
}

void MoveRitual::castCard() {
  if (board->getMagic(this->getOwner()) >= this->getActCost() && this->getCharges() > 0) {
    board->setMagic(this->getOwner(), board->getMagic(this->getOwner()) - this->getActCost());
    this->setCharges(this->getCharges() - 1);
    //Requires implementation
  }
}

void MoveRitual::castCard(int p, int t) {

}
