#include "triggered.h"

using namespace std;

Triggered::Triggered(string &name, int cost, int owner, string &description, Event trigger) :
        Ability(name, cost, owner, description) {}