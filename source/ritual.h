#ifndef RITUAL_H
#define RITUAL_H

#include "nonplayer.h"

class Ritual: public NonPlayer {
    int charges;
    int activationCost;
    Event trigger;
public:
    Ritual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, Event trigger):
        NonPlayer{cardName, cost, owner, description}, charges{charges}, activationCost{activationCost}, trigger{trigger} {
            type = Type::Ritual;
        }
    virtual ~Ritual() = default;
};

class AddPlayerRitual: public Ritual {
    int healthMod;
    int magicMod;
    std::string target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    AddPlayerRitual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, int healthMod, int magicMod, Event trigger, std::string &target);
    ~AddPlayerRitual() { }
};

class AddMinionRitual: public Ritual {
    int attMod;
    int defMod;
    int actPerTurn;
    int abilityCost;
    bool silence = false;
    std::string target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    AddMinionRitual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, int attMod, int defMod, int actPerTurn, int abilityCost, int silencer, Event trigger, std::string &target);
    ~AddMinionRitual() { }
};

class MoveRitual: public Ritual {
    std::string target;
    std::string destination;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    MoveRitual(std::string &cardName, int cost, int owner, std::string &description, int charges, int activationCost, Event trigger, std::string &target, std::string &destination);
    ~MoveRitual() { }
};

#endif
