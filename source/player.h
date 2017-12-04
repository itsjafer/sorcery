#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "card.h"

class NonPlayer;
class Ritual;
class Minion;

class Player: public Card {
    friend BoardModel;
    int health = 20;
    int magic = 3;
    std::vector<std::shared_ptr<NonPlayer>> deck;
    std::vector<std::shared_ptr<NonPlayer>> hand;
    std::shared_ptr<Ritual> ritual = nullptr;
    std::vector<std::shared_ptr<NonPlayer>> graveyard;
    std::vector<std::shared_ptr<Minion>> minions;
    int playerNumber;
    void addCard(std::ifstream &cardData);
    void updateState(std::vector<Event> &events) override;
public:
    Player(std::string &name, std::unique_ptr<std::ifstream> &deck, int playerNumber);
    void drawCard(int numCards = 1);
    Minion &minion(int i);                                  //to be used by displays (i.e. Observers)
    void shuffleDeck();                                //to be used by displays (i.e. Observers)
    const std::vector<std::shared_ptr<NonPlayer>> &getHand() const;     //same here
    void play(int i);                                                   //non-targetted spells & rituals, as well as placing minions on the field
    void play(int i, int p, int t = -1);                              //spells (w/ target) & enchantments
    void use(int i);                                                    //untargetted activated ability of ith minion
    void use(int i, int p, int t = -1);                               //targetted activated ability of ith minion
    void attack(int i, int j = 0);
    void toGrave(bool Ritual, int minionIndex);
    ~Player();
};

#endif
