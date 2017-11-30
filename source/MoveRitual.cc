#include "ritual.h"

using namespace std;

MoveRitual::MoveRitual(string &cardName, int cost, int owner, string &description, int charges, int activationCost, Event trigger,
                       string &target, string &destination):
Ritual(cardName, cost, owner, description, charges, activationCost, trigger), target(target), destination(destination){}

void MoveRitual::updateState(vector<Event> &events) {

}

void MoveRitual::castCard() {

}

void MoveRitual::castCard(int p, char t) {

}
