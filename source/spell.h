#ifndef SPELL_H
#define SPELL_H

#include "nonplayer.h"

class Spell: public NonPlayer {
public:
    Spell(std::string &name, int cost, int owner, std::string &description);
    virtual ~Spell() = 0;
};

class MoveSpell: public Spell {
    std::string moveSource;
    std::string moveDestination;
    std::string Target;
public:
    MoveSpell(std::string &cardName, int cost, int owner, std::string &description, std::string &moveSource, std::string &moveDestination, std::string &Target);
};

class AddSpell: public Spell {
    int attMod;
    int defMod;
    std::string Target;
public:
    AddSpell(std::string &cardName, int cost, int owner, std::string &description, int attMod, int defMod, std::string &Target);
};
class MoveAddSpell: public Spell {
    int attMod;
    int defMod;
    std::string moveSource;
    std::string moveDestination;
    std::string Target;
public:
    MoveAddSpell(std::string &cardName, int cost, int owner, std::string &description, int attMod, int defMod, std::string &moveSource, std::string &moveDestination,  std::string &Target);
};

class AddRitualSpell: public Spell {
    int chargeMod;
    int costMod;
public:
    AddRitualSpell(std::string &cardName, int cost, int owner, std::string &description, int chargeMod, int costMod);
};

#endif
