#include "ritual.h"
#include "minion.h"
#include <iostream>

using namespace std;

MoveRitual::MoveRitual(string &cardName, int cost, int owner, string &description, int charges, int activationCost, Event trigger,
                       string &target, string &destination):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), target(target), destination(destination){}

void MoveRitual::updateState(vector<Event> &events) {

  //Go through list of given events
  for (int i = 0; i < events.size(); ++i) {
    //check the event and if it triggers this ability
    if (events[i] == this->getTrigger()) {
      for (int j = 0; j < events.size(); ++j) {
        if (events[j] == Event::enemyMinionEnteredPlay) {
          onOwn = false;
          this->castCard();
        } else if (events[j] == Event::minionEnteredPlayControlled) {
          onOwn = true;
          this->castCard();
        }
      }
    }
  }
}

void MoveRitual::castCard() {
  if (board->getMagic(this->getOwner()) < this->getActCost() && !(board->testingMode)) throw InvalidMoveException(InvalidMove::InsufficientMagicRitual);
  if (this->getCharges() < 0) throw InvalidMoveException(InvalidMove::NoChargesLeft);

  board->setMagic(this->getOwner(), board->getMagic(this->getOwner()) - this->getActCost());
  if (board->getMagic(this->getOwner()) < 0) board->setMagic(this->getOwner(), 0);
  this->setCharges(this->getCharges() - 1);
  //Requires implementation
  vector<Event> EventsForTarget;
  if (onOwn) {
    EventsForTarget.emplace_back(Event::minionDied);
    board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).update(EventsForTarget);
    board->players.at(this->getOwner())->toGrave(false, board->players.at(this->getOwner())->numMinions() - 1);
  } else {
    int opponent;
    if (this->getOwner() == 1) {
      opponent = 0;
    } else if (this->getOwner() == 0) {
      opponent = 1;
    }

    EventsForTarget.emplace_back(Event::minionDied);
    board->players.at(opponent)->minion(board->players.at(opponent)->numMinions()).update(EventsForTarget);
    board->players.at(opponent)->toGrave(false, board->players.at(opponent)->numMinions() - 1);
  }
}

void MoveRitual::castCard(int p, int t) {

}
