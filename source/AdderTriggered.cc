#include "triggered.h"
#include <iostream>

using namespace std;

AdderTriggered::AdderTriggered(int owner, Event trigger, int attMod, int defMod, string &target, string &description, Minion *minion):
        Triggered(description, 0, owner, description, trigger, minion), attMod(attMod), defMod(defMod), target(target) {}

void AdderTriggered::updateState(vector<Event> &events) {
  //Go through list of given events
  for (int i = 0; i < events.size(); ++i) {
    //check the event and if it triggers this ability
    if (events[i] == this->getTrigger()) {
      this->castCard();
    }
  }

}

void AdderTriggered::castCard() {
  if (target == "all of own") {
    //Go thrugh all personal minions
    for (int i = 0; i < board->players.at(this->getOwner())->numMinions(); ++i) {
      vector<Event> EventsForTarget;

      //Apply affects to minion
      board->players.at(this->getOwner())->minion(i + 1).att += attMod;
      board->players.at(this->getOwner())->minion(i + 1).def += defMod;

      //update that minion
      if (defMod < 0) {
        //Minion took damage
        EventsForTarget.emplace_back(Event::minionTookDamage);

        if (board->players.at(this->getOwner())->minion(i + 1).def <= 0) {

          //Minion died
          EventsForTarget.emplace_back(Event::minionDied);
          board->players.at(this->getOwner())->minion(i + 1).update(EventsForTarget);
          board->players.at(this->getOwner())->toGrave(false, i);

        } else {
          board->players.at(this->getOwner())->minion(i + 1).update(EventsForTarget);
        }
      }

    }
  } else if (target == "this minion") {
    vector<Event> EventsForTarget;

    //Apply affects to minion
    this->minion->att += attMod;
    this->minion->def += defMod;

  } else if (target == "trigger target") {
    vector<Event> EventsForTarget;

    int opponent;
    if (this->getOwner() == 0) {
      opponent = 1;
    } else if (this->getOwner() == 1) {
      opponent = 0;
    }

    int back = board->players.at(opponent)->numMinions();
    //Apply affects to minion
    board->players.at(opponent)->minion(back).att += attMod;
    board->players.at(opponent)->minion(back).def += defMod;

    //update that minion
    if (defMod < 0) {
      //Minion took damage
      EventsForTarget.emplace_back(Event::minionTookDamage);

      if (board->players.at(opponent)->minion(back).def <= 0) {

        //Minion died
        EventsForTarget.emplace_back(Event::minionDied);
        board->players.at(opponent)->minion(back).update(EventsForTarget);
        board->players.at(opponent)->toGrave(false, back - 1);

      } else {
        board->players.at(opponent)->minion(back).update(EventsForTarget);
      }
    }
  }
}

void AdderTriggered::castCard(int p, int t) {

}
