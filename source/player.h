#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "card.h"

class NonPlayer;

class Player: public Card {
    friend BoardModel;
    int health = 20;
    int magic = 3;
    std::vector<std::unique_ptr<NonPlayer>> hand;
    NonPlayer *ritual;
    std::vector<std::unique_ptr<NonPlayer>> graveyard;
    std::vector<std::unique_ptr<NonPlayer>> minions;
    int playerNumber;
public:
    Player(std::string &name, std::string &deck);
    void drawCard(int numCards = 1);
    NonPlayer &minion(int i);
    std::vector<std::unique_ptr<NonPlayer>> &getHand();
    void play(int i);
    void play(int i, int p, char t = 'r');
    void use(int i);
    void use(int i, int p, char t = 'r');
    void attack(int i, int j = 0);
    ~Player();
};

#endif
