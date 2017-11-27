#include "activated.h"


AdderActive::AdderActive(std::string &name, int cost, int owner, std::string &description, int attMod, int defMod, std::string &target):
        Activated(name, cost, owner, description), attMod(attMod), defMod(defMod), target(target) {}

