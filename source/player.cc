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
        int cardAttack;
        cardData >> cardAttack;
        int cardDefense; 
        cardData >> cardDefense;
        vector<ifstream> cardAbilityFiles;
        string ability;
        while (getline(cardData, ability)) {
            cardAbilityFiles.emplace_back(move(ability));
        }

        deck.emplace_back(make_shared<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
        //deck.emplace_back(make_unique<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
    }
    else if (cardType == "Spell") {

    }
    else if (cardType == "Ritual") {

    }
    else {  //cardType == "Enhancement"

    }
}

void Player::updateState(vector<Event> &events) {
    for (int i = 0; i < minions.size(); ++i) minions.at(i)->update(events);
    ritual->update(events);
}

void Player::drawCard(int numCards) {
    if (deck.size() > 0) {
        hand.emplace_back(deck.back());    //not sure if this actually works...
        deck.pop_back();
    }
    else throw out_of_range(getName());
}

const Minion &Player::minion(int i) const {
    return *(minions.at(i - 1));
}

const vector<shared_ptr<NonPlayer>> &Player::getHand() const {
    return hand;
}

void Player::play(int i) {
    auto card = hand.at(i - 1);

    if (card->getType() == Type::Spell) {
        card->cast();               //will update the board: no need to do in here
        graveyard.emplace_back(card);
    }
    else if (card->getType() == Type::Ritual) {
        ritual = card;
    }
    else if (card->getType() == Type::Minion) {
        minions.emplace_back(card);
    }
    else { }    //handle exception

    hand.erase(hand.begin() + (i - 1));     //remove card from hand
}

void Player::play(int i, int p, char t = 'r') {
    auto card = hand.at(i - 1);

    if (card->getType() == Type::Spell) {
        card->cast(p, t);               //will update the board: no need to do in here
        graveyard.emplace_back(card);
    }
    else if (card->getType() == Type::Enchantment) {
        card->cast(p, t);
        minions.at((int)(t - 1))->enchantments.emplace_back(card);
    }
    else { }    //handle exception

    hand.erase(hand.begin() + (i - 1));     //remove card from hand
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
    deck.clear();
    graveyard.clear();
    hand.clear();
    minions.clear();
}
