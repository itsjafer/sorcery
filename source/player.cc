#include "player.h"
#include "minion.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

Player::Player(string &name, unique_ptr<ifstream> &deck): Card{name} {
    string cardFile;
    while (getline(*deck, cardFile)) {
        ifstream cardData{cardFile};
        addCard(cardData);
    }
}

void Player::addCard(ifstream &cardData) {
    // Read in card data from the ifstream
    string cardType;
    getline(cardData, cardType);
    if (cardType == "Spell") { }    //Spell requires that we read in the type of Spell
    string cardName; 
    getline(cardData, cardName);
    int cardCost;
    cardData >> cardCost;

    if (cardType == "Minion") {

    }
    else if (cardType == "Spell") {

    }
    else if (cardType == "Ritual") {

    }
    else {  //cardType == "Enhancement"

    }
}

void Player::updateState(vector<Event> &events) {
}

void Player::drawCard(int numCards) {
}

const Minion &Player::minion(int i) const {
    return *(minions.at(i - 1));
}

const vector<shared_ptr<NonPlayer>> &Player::getHand() const {
    return hand;
}

void Player::play(int i) {
}

void Player::play(int i, int p, char t) {
}

void Player::use(int i) {
}
    
void Player::use(int i, int p, char t) {
}

void Player::attack(int i, int j) {
}

Player::~Player() {
    deck.clear();
    graveyard.clear();
    hand.clear();
    minions.clear();
}
