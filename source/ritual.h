#ifndef RITUAL_H
#define RITUAL_H

#include "nonplayer.h"

class Ritual: public NonPlayer {
    int charges;
    int activationCost;
    Event trigger;
public:
    Ritual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, Event trigger);
    virtual ~Ritual() = 0;
};

class AddPlayerRitual: public Ritual {
    int healthMod;
    int magicMod;
    std::string target;
public:
    AddPlayerRitual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, int healthMod, int magicMod, Event trigger, std::string &target);
};

class AddMinionRitual: public Ritual {
    int attMod;
    int defMod;
    int actPerTurn;
    int abilityCost;
    bool silence = false;
    std::string target;
public:
    AddMinionRitual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, int attMod, int defMod, int actPerTurn, int abilityCost, int silencer, Event trigger, std::string &target);
};

class MoveRitual: public Ritual {
    std::string target;
    std::string destination;
public:
    MoveRitual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, Event trigger, std::string &target, std::string &destination);
};

#endif
