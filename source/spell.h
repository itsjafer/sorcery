#ifndef SPELL_H
#define SPELL_H

#include "nonplayer.h"

class Spell: public NonPlayer {
public:
    virtual ~Spell() = 0;
};

class MoveSpell: public Spell {
    std::string moveSource;
    std::string moveDestination;
    std::string Target;
public:
    MoveSpell(std::string &cardName, int cost, int owner, std::string &moveSource, std::string &moveDestination, std::string &Target, std::string &&description);
};

class AddSpell: public Spell {
    int attMod;
    int defMod;
    std::string Target;
public:
    AddSpell(std::string &cardName, int cost, int attMod, int defMod, int owner, std::string &Target, std::string &&description);
};

#endif
