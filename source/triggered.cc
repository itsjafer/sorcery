#include "triggered.h"

using namespace std;

Triggered::Triggered(string &name, int cost, int owner, string &description, Event trigger, Minion *minion) :
        Ability(name, 0, owner, description, minion), trigger(trigger) {
                type = Type::TriggeredAbility;
        }

Event Triggered::getTrigger() {
  return trigger;
}
