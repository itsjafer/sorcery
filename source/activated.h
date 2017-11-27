#ifndef ACTIVATED_H
#define ACTIVATED_H

#include "ability.h"

class Activated: public Ability {
public:
    Activated();
    virtual ~Activated() = 0;
};

class AdderActive: public Activated {
    int attMod;
    int defMod;
    std::string target;
public:
    AdderActive(int cost, int attMod, int defMod, std::string target, std::string description);
};

#endif
