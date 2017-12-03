#include "triggered.h"
#include <iostream>

using namespace std;

AdderTriggered::AdderTriggered(int owner, Event trigger, int attMod, int defMod, string &target, string &description, Minion *minion):
        Triggered(description, owner, 0, description, trigger, minion), attMod(attMod), defMod(defMod), target(target) {}

void AdderTriggered::updateState(vector<Event> &events) {
  cout << "Checking for triggers under " << events.size() << " events" << endl;
  //Go through list of given events
  for (int i = 0; i < events.size(); ++i) {
    //check the event and if it triggers this ability
    if (events[i] == this->getTrigger()) {
      cout << "Ability triggerd: " << this->getDescription() << endl;;
      this->castCard();
    }
  }

}

void AdderTriggered::castCard() {
  if (target == "all of own") {
    //Go thrugh all personal minions
    cout << "Apply to " << board->players.at(this->getOwner())->numMinions() << " minions" << endl;
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
          board->players.at(this->getOwner())->minion(i).update(EventsForTarget);
          board->players.at(this->getOwner())->toGrave(false, i + 1);

        } else {
          board->players.at(this->getOwner())->minion(i).update(EventsForTarget);
        }
      }

    }
  } else if (target == "this minion") {
    vector<Event> EventsForTarget;

    //Apply affects to minion
    this->minion->att += attMod;
    this->minion->def += defMod;

  }
}

void AdderTriggered::castCard(int p, char t) {

}
