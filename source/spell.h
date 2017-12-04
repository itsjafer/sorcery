#ifndef SPELL_H
#define SPELL_H

#include "nonplayer.h"
#include "playercontroller.h"
#include "minion.h"

class Spell: public NonPlayer {
public:
    Spell(std::string &name, int cost, int owner, std::string &description): NonPlayer{name, cost, owner, description} {type = Type::Spell;}
    virtual ~Spell() = default;
};

class MoveSpell: public Spell {
    std::string moveSource;
    std::string moveDestination;
    std::string Target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    MoveSpell(std::string &cardName, int cost, int owner, std::string &description, std::string &moveSource, std::string &moveDestination, std::string &Target);
    ~MoveSpell() { }
};

class AddSpell: public Spell {
    int attMod;
    int defMod;
    std::string attOperation;
    std::string defOperation;
    std::string Target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    AddSpell(std::string &cardName, int cost, int owner, std::string &description, int attMod, int defMod, std::string attOperation, std::string defOperation, std::string &Target);
    ~AddSpell() { }
};
class MoveAddSpell: public Spell {
    int attMod;
    int defMod;
    std::string attOperation;
    std::string defOperation;
    std::string moveSource;
    std::string moveDestination;
    std::string Target;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    MoveAddSpell(std::string &cardName, int cost, int owner, std::string &description, int attMod, int defMod, std::string attOperation, std::string defOperation, std::string &moveSource, std::string &moveDestination,  std::string &Target);
    ~MoveAddSpell() { }
};

class AddRitualSpell: public Spell {
    int chargeMod;
    int costMod;
    void updateState(std::vector<Event> &events) override;
    void castCard() override;
    void castCard(int p, int t = -1) override;
public:
    AddRitualSpell(std::string &cardName, int cost, int owner, std::string &description, int chargeMod, int costMod);
    ~AddRitualSpell() { }
};

#endif
