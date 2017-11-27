#ifndef ACTIVATED_H
#define ACTIVATED_H

#include "ability.h"

class Activated: public Ability {
public:
    Activated(std::string &name, int cost, int owner, std::string &description);
    virtual ~Activated() = 0;
};

class AdderActive: public Activated {
    int attMod;
    int defMod;
    std::string target;
public:
    AdderActive(std::string &name, int cost, int owner, std::string &description, int attMod, int defMod, std::string &target);
};

#endif
