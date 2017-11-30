#ifndef SPELL_H
#define SPELL_H

#include "nonplayer.h"

class Spell: public NonPlayer {
public:
    Spell(std::string &name, int cost, int owner, std::string &description): NonPlayer{name, cost, owner, description} {type = Type::Spell;}
    virtual ~Spell() = 0;
};

class MoveSpell: public Spell {
    std::string moveSource;
    std::string moveDestination;
    std::string Target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    MoveSpell(std::string &cardName, int cost, int owner, std::string &description, std::string &moveSource, std::string &moveDestination, std::string &Target);
};

class AddSpell: public Spell {
    int attMod;
    int defMod;
    std::string Target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, char t = 'r') override;
public:
    AddSpell(std::string &cardName, int cost, int owner, std::string &description, int attMod, int defMod, std::string &Target);
};

#endif
