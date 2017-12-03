#include "activated.h"
#include <iostream>

using namespace std;

AdderActive::AdderActive(string &name, int cost, int owner, string &description, int attMod, int defMod, string &target, Minion *minion):
        Activated(name, cost, owner, description, minion), attMod(attMod), defMod(defMod), target(target) {}

void AdderActive::updateState(vector<Event> &events) {

}

void AdderActive::castCard() {

}

void AdderActive::castCard(int p, char t) {
  //If this ability takes a target do something to the target
  vector<Event> EventsForTarget;
  cout << "Applying ability: "  << this->getDescription() << endl;
  if (target == "chosen") { //cannot be a ritual
    int target = t;
    //Check if they have enough magic
    if (board->getMagic(this->getOwner()) >= this->getCost()) {

      //Subtract from magic
      board->setMagic(this->getOwner(), board->getMagic(this->getOwner()) - this->getCost());
      cout << "Used magic" << endl;
      cout << "Player: " << p << endl;
      cout << "Target: " << target << endl;

      //execute ability
      board->players.at(p)->minion(target).def += defMod;
      board->players.at(p)->minion(target).att += attMod;
      cout << "Applied effects" << endl;

      //update that minion
      if (defMod < 0) {
        //Minion took damage
        EventsForTarget.emplace_back(Event::minionTookDamage);

        if (board->players.at(p)->minion  (target).def <= 0) {

          //Minion died
          EventsForTarget.emplace_back(Event::minionDied);
          board->players.at(p)->minion(target).update(EventsForTarget);
          board->players.at(p)->toGrave(false, target);

        } else {
          board->players.at(p)->minion(target).update(EventsForTarget);
        }
      }
    }
  } else if (target == "ritual") {

  }
}
