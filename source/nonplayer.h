#ifndef NONPLAYER_H
#define NONPLAYER_H

#include "card.h"
#include "type.h"

class NonPlayer: public Card {
    int cost;
    int owner;
    std::string description;
    virtual void castCard() = 0;
    virtual void castCard(int p, int t = -1) = 0;
protected:
    Type type;
public:
    NonPlayer(std::string &name, int cost, int owner, std::string description = "");
    void cast();
    void cast(int p, int t = -1);
    int getCost();
    void setCost(int cost);
    int getOwner();
    void setOwner(int owner);
    std::string getDescription();
    const Type getType() const;
    virtual ~NonPlayer() = default;
};

#endif
