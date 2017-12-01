#include "activated.h"

using namespace std;

SummonActive::SummonActive(string &name, int cost, int owner, string &description, int summonAmount,
                           string &summonMinion):
Activated(name, cost, owner, description), summonAmount(summonAmount), summonMinion(summonMinion){}

void SummonActive::updateState(vector<Event> &events) {

}

void SummonActive::castCard() {

}

void SummonActive::castCard(int p, char t) {

}