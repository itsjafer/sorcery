#include "player.h"
#include "minion.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

Player::Player(string &name, ifstream &deck): Card{name} {
    string cardFile;
    while (getline(deck, cardFile)) {
        ifstream cardData{cardFile};
        addCard(cardData);
    }
}

void Player::addCard(ifstream &cardData) {
    string cardType; getline(cardData, cardType);
    if (cardType == "Spell") { }
    string cardName; getline(cardData, cardName);
    int cardCost; cardData >> cardCost;

    if (cardType == "Minion") {
        int cardAttack; cardData >> cardAttack;
        int cardDefense; cardData >> cardDefense;
        vector<ifstream> cardAbilityFiles;
        string ability;
        while (getline(cardData, ability)) {
            cardAbilityFiles.emplace_back(move(ability));
        }

        deck.emplace_back(make_unique<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
    }
    else if (cardType == "Spell") {

    }
    else if (cardType == "Ritual") {

    }
    else {  //cardType == "Enhancement"

    }
}

void Player::drawCard(int numCards) {
    if (deck.size() > 0) {
        auto card = move(deck.back());
        deck.pop_back();
        hand.emplace_back(move(card));
    }
    else throw out_of_range(getName());
}

const Minion &Player::minion(int i) const {
    return *(minions.at(i - 1));
}

const vector<unique_ptr<NonPlayer>> &Player::getHand() const {
    return hand;
}

void Player::play(int i) {
    
}

void Player::play(int i, int p, char t) {

}

void Player::use(int i) {
    minions.at(i - 1)->cast();
}
    
void Player::use(int i, int p, char t = 'r') {
    minions.at(i - 1)->cast(p, t);
}

void Player::attack(int i, int j = 0) {
    minions.at(i - 1)->attack(j);
}

Player::~Player() {

}
