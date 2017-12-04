#ifndef ACTIVATED_H
#define ACTIVATED_H

#include "ability.h"

class Activated: public Ability {
public:
    Activated(std::string &name, int cost, int owner, std::string &description, Minion *minion);
    virtual ~Activated() = default;
};

class AdderActive: public Activated {
    int attMod;
    int defMod;
    std::string target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    AdderActive(std::string &name, int cost, int owner, std::string &description, int attMod, int defMod, std::string &target, Minion *minion);
    ~AdderActive() { }
};

class SummonActive: public  Activated {
    int summonAmount;
    std::string summonMinion;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    SummonActive(std::string &name, int cost, int owner, std::string &description, int summonAmount, std::string &summonMinion, Minion *minion);
    ~SummonActive() { }
};

#endif
