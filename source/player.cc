#include "player.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

Player::Player(string &name, unique_ptr<ifstream> &deck): Card{name} {
    string cardFile;
    while (getline(*deck, cardFile)) {
        cardFile += ".card"; // adding the card extension
        ifstream cardData{cardFile};
        addCard(cardData);
    }
}

void Player::addCard(ifstream &cardData) {

    //Get card type {spell, minion, enchantment, ritual}
    string cardType; getline(cardData, cardType);

    if (cardType == "Minion") {
        //Adding a minion type
        string cardName; getline(cardData, cardName);
        int cardCost; cardData >> cardCost;
        int cardAttack; cardData >> cardAttack;
        int cardDefense; cardData >> cardDefense;


        vector<ifstream> cardAbilityFiles;
        string ability;
        while (getline(cardData, ability)) {
            cardAbilityFiles.emplace_back(move(ability));
        }

        deck.emplace_back(make_shared<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
        //deck.emplace_back(make_unique<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
    }
    else if (cardType == "Spell") {
        //Adding a spell card
        //Get spell type
        string spellType; getline(cardData, spellType);
        if (spellType == "move") {

            //Get move source
            string moveSrc; getline(cardData, moveSrc);

            //Get move destination
            string moveDest; getline(cardData, moveDest);

            //Get Target
            string target; getline(cardData, target);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new MoveSpell(cardName, cardCost, playerNumber, cardDscr, moveSrc, moveDest, target));
            deck.emplace_back(newSpell);
        } else if (spellType == "add") {

            //Get Target and modifiers
            string target; getline(cardData, target);
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            string attFier; getline(cardData, attFier);
            string defFier; getline(cardData, defFier);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new AddSpell(cardName, cardCost, playerNumber, cardDscr, attMod, defMod, attFier, defFier, target));
            deck.emplace_back(newSpell);
        } else if (spellType == "moveAdd") {
            //Get move source
            string moveSrc; getline(cardData, moveSrc);
            //Get move destination
            string moveDest; getline(cardData, moveDest);
            //Get Target
            string target; getline(cardData, target);

            //Get Target and modifiers
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            string attFier; getline(cardData, attFier);
            string defFier; getline(cardData, defFier);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);
            //Create card
            shared_ptr<Spell> newSpell(new MoveAddSpell(cardName, cardCost, playerNumber, cardDscr, attMod, defMod, attFier, defFier, moveSrc, moveDest, target));
            deck.emplace_back(newSpell);

        } else if (spellType == "ritualMod") {

            //Get Target and modifiers
            int chargeMod; cardData >> chargeMod;
            int costMod; cardData >> costMod;

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new AddRitualSpell(cardName, cardCost, playerNumber, cardDscr, chargeMod, costMod));
            deck.emplace_back(newSpell);
        }
    }
    else if (cardType == "Ritual") {
        //Adding a ritual card
        string ritualType; getline(cardData, ritualType);
        if (ritualType == "add") {
            string target; getline(cardData, target);
            if (target == "player") {

                //Get Ritual basics
                int activeCost; cardData >> activeCost;
                int charges; cardData >> charges;
                Event cardTrigger;
                string trigger; getline(cardData, trigger);
                if (trigger == "Beginning of turn") {
                    cardTrigger = Event::startTurn;
                } else if (trigger == "Enter controlled") {
                    cardTrigger = Event::minionEnteredPlay; //Note incorrect event type for now, will change later
                } else if (trigger == "Enter any") {
                    cardTrigger = Event::minionEnteredPlay;
                }

                //Get player modifiers
                int healthMod; cardData >> healthMod;
                int magicMod; cardData >> magicMod;
                string targets; getline(cardData, targets);

                //Name and Cost and decsription
                string cardName; getline(cardData, cardName);
                int cardCost; cardData >> cardCost;
                string cardDscr; getline(cardData, cardDscr);

                //Create card
                shared_ptr<Ritual> newRitual(new AddPlayerRitual(cardName, cardCost, playerNumber, cardDscr, charges, activeCost, healthMod, magicMod, cardTrigger, targets));
                deck.emplace_back(newRitual);
            } else if (target == "minion") {

                //Get modifiers
                //Get Ritual basics
                int activeCost; cardData >> activeCost;
                int charges; cardData >> charges;

                Event cardTrigger;
                string trigger; getline(cardData, trigger);
                if (trigger == "Beginning of turn") {
                    cardTrigger = Event::startTurn;
                } else if (trigger == "Enter controlled") {
                    cardTrigger = Event::minionEnteredPlay; //Note incorrect event type for now, will change later
                } else if (trigger == "Enter any") {
                    cardTrigger = Event::minionEnteredPlay;
                }
                int attMod; cardData >> attMod;
                int defMod; cardData >> defMod;
                int actPerTurn; cardData >> actPerTurn;
                int abilityCost; cardData >> abilityCost;
                int silenced; cardData >> silenced;
                string target; getline(cardData, target);

                //Name and Cost and decsription
                string cardName; getline(cardData, cardName);
                int cardCost; cardData >> cardCost;
                string cardDscr; getline(cardData, cardDscr);

                //Create card
                shared_ptr<Ritual> newRitual(new AddMinionRitual(cardName, cardCost, playerNumber, cardDscr, charges, activeCost, attMod, defMod,actPerTurn, abilityCost, silenced, cardTrigger, target));
                deck.emplace_back(newRitual);
            }
        } else if (ritualType == "move") {
            //Get Ritual basics
            int activeCost; cardData >> activeCost;
            int charges; cardData >> charges;

            Event cardTrigger;
            string trigger; getline(cardData, trigger);
            if (trigger == "Beginning of turn") {
                cardTrigger = Event::startTurn;
            } else if (trigger == "Enter controlled") {
                cardTrigger = Event::minionEnteredPlay; //Note incorrect event type for now, will change later
            } else if (trigger == "Enter any") {
                cardTrigger = Event::minionEnteredPlay;
            }

            //Move data
            string target; getline(cardData, target);
            string destination; getline(cardData, destination);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Ritual> newRitual(new MoveRitual(cardName, cardCost, playerNumber, cardDscr, charges, activeCost, cardTrigger, target, destination));
            deck.emplace_back(newRitual);
        }
    }
    else if (cardType == "Enchantment") {  //cardType == "Enhancement"
        //Get ritual type
        string enchantType; getline(cardData, enchantType);
        if (enchantType == "add") {

            //Get modifiers
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            int actPerTurn; cardData >> actPerTurn;
            int abilityCost; cardData >> abilityCost;
            int silenced; cardData >> silenced;
            string attFier; getline(cardData, attFier);
            string defFier; getline(cardData, defFier);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Enchantment> newEnchantment(new AddEnchant(cardName, cardCost, playerNumber, cardDscr, attMod, defMod, actPerTurn, abilityCost, attFier, defFier, silenced));
            deck.emplace_back(newEnchantment);
        }
    }
}

void Player::updateState(vector<Event> &events) {
    for (int i = 0; i < minions.size(); ++i) minions.at(i)->update(events);
    ritual->update(events);
}

void Player::drawCard(int numCards) {
    if (deck.size() > 0) {
        for (int i = 0; i < numCards; ++i)
        {
            hand.emplace_back(deck.back());    //not sure if this actually works...
            deck.pop_back();
        }
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
        ritual = dynamic_pointer_cast<Ritual>(card);
    }
    else if (card->getType() == Type::Minion) {
        minions.emplace_back(dynamic_pointer_cast<Minion>(card));
    }
    else { }    //handle exception

    hand.erase(hand.begin() + (i - 1));     //remove card from hand
}

void Player::play(int i, int p, char t) {
    auto card = hand.at(i - 1);

    if (card->getType() == Type::Spell) {
        card->cast(p, t);               //will update the board: no need to do in here
        graveyard.emplace_back(card);
    }
    else if (card->getType() == Type::Enchantment) {
        card->cast(p, t);
        minions.at((int)(t - 1))->enchantments.emplace_back(dynamic_pointer_cast<Enchantment>(card));
    }
    else { }    //handle exception

    hand.erase(hand.begin() + (i - 1));     //remove card from hand
}

void Player::use(int i) {
    minions.at(i - 1)->cast();
}
    
void Player::use(int i, int p, char t) {
    minions.at(i - 1)->cast(p, t);
}

void Player::attack(int i, int j) {
    minions.at(i - 1)->attack(j);
}

Player::~Player() {
    deck.clear();
    graveyard.clear();
    hand.clear();
    minions.clear();
}
