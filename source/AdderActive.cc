#include "activated.h"

using namespace std;

AdderActive::AdderActive(string &name, int cost, int owner, string &description, int attMod, int defMod, string &target):
        Activated(name, cost, owner, description), attMod(attMod), defMod(defMod), target(target) {}

void AdderActive::updateState(vector<Event> &events) {

}

void AdderActive::castCard() {

}

void AdderActive::castCard(int p, char t) {

}
