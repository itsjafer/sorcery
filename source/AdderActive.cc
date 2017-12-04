#include "activated.h"
#include <iostream>

using namespace std;

AdderActive::AdderActive(string &name, int cost, int owner, string &description, int attMod, int defMod, string &target, Minion *minion):
        Activated(name, cost, owner, description, minion), attMod(attMod), defMod(defMod), target(target) {
          this->type = Type::ActivatedAbility;
        }

void AdderActive::updateState(vector<Event> &events) {

}

void AdderActive::castCard() {

}

void AdderActive::castCard(int p, int t) {
  //If this ability takes a target do something to the target
  vector<Event> EventsForTarget;
  if (target == "chosen") { //cannot be a ritual
    int target = t;

    //execute ability
    board->players.at(p)->minion(target).def += defMod;
    board->players.at(p)->minion(target).att += attMod;

    //update that minion
    if (defMod < 0) {
      //Minion took damage
      EventsForTarget.emplace_back(Event::minionTookDamage);

      if (board->players.at(p)->minion(target).def <= 0) {

        //Minion died
        EventsForTarget.emplace_back(Event::minionDied);
        board->players.at(p)->minion(target).update(EventsForTarget);
        board->players.at(p)->toGrave(false, target - 1);

      } else {
        board->players.at(p)->minion(target).update(EventsForTarget);
      }
    }

  } else if (target == "ritual") {

  }
}
