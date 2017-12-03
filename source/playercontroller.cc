#include "playercontroller.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <cstdlib>
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"

using namespace std;

PlayerController::PlayerController(string &name, unique_ptr<ifstream> &deck, int playerNumber): Card{name}, playerModel(name, playerNumber) {
    string cardFile;
    while (getline(*deck, cardFile)) {
        cardFile += ".card"; // adding the card extension
        ifstream cardData{cardFile};
        addCard(cardData);
    }

    // set the random number generator to the current time
    srand (time (0));
    shuffleDeck();
}

void PlayerController::shuffleDeck() {
    // using this to get a random num gen
    std::random_shuffle(playerModel.deck.begin(), playerModel.deck.end());
}

void PlayerController::addCard(ifstream &cardData) {

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

        playerModel.deck.emplace_back(make_shared<Minion>(cardName, cardCost, playerModel.playerNumber, cardAttack, cardDefense, cardAbilityFiles));
        //deck.emplace_back(make_unique<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
    }
    else if (cardType == "Spell") {
        //Adding a spell card
        //Get spell type

        string spellType; getline(cardData, spellType);

        cout << "Player.cc: Im making a " << spellType << " spell!" << endl;
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

            // skip to the next line
            cardData.ignore(10000, '\n');

            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new MoveSpell(cardName, cardCost, playerModel.playerNumber, cardDscr, moveSrc, moveDest, target));
            playerModel.deck.emplace_back(newSpell);
        } else if (spellType == "add") {

            //Get Target and modifiers
            string target; getline(cardData, target);
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            // skip to the next line
            cardData.ignore(10000, '\n');
            string attOperation; getline(cardData, attOperation);
            string defOperation; getline(cardData, defOperation);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;

            cardData.ignore(10000, '\n');
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new AddSpell(cardName, cardCost, playerModel.playerNumber, cardDscr, attMod, defMod, attOperation, defOperation, target));
            playerModel.deck.emplace_back(newSpell);
        } else if (spellType == "moveAdsd") {
            //Get move source
            string moveSrc; getline(cardData, moveSrc);
            //Get move destination
            string moveDest; getline(cardData, moveDest);
            //Get Target
            string target; getline(cardData, target);

            //Get Target and modifiers
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            string attOperation; getline(cardData, attOperation);
            string defOperation; getline(cardData, defOperation);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            // skip to the next line
            cardData.ignore(10000, '\n');
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new AddSpell(cardName, cardCost, playerModel.playerNumber, cardDscr, attMod, defMod, attOperation, defOperation, target));
            playerModel.deck.emplace_back(newSpell);
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
            // skip to the next line
            cardData.ignore(10000, '\n');
            string attOperation; getline(cardData, attOperation);
            string defOperation; getline(cardData, defOperation);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            // skip to the next line
            cardData.ignore(10000, '\n');
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new MoveAddSpell(cardName, cardCost, playerModel.playerNumber, cardDscr, attMod, defMod, attOperation, defOperation, moveSrc, moveDest, target));
            playerModel.deck.emplace_back(newSpell);

        } else if (spellType == "ritualMod") {

            //Get Target and modifiers
            int chargeMod; cardData >> chargeMod;
            int costMod; cardData >> costMod;

            // skip to the next line
            cardData.ignore(10000, '\n');

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            // skip to the next line
            cardData.ignore(10000, '\n');
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Spell> newSpell(new AddRitualSpell(cardName, cardCost, playerModel.playerNumber, cardDscr, chargeMod, costMod));
            playerModel.deck.emplace_back(newSpell);
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
                // skip to the next line
                cardData.ignore(10000, '\n');
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
                // skip to the next line
                cardData.ignore(10000, '\n');
                string targets; getline(cardData, targets);

                //Name and Cost and decsription
                string cardName; getline(cardData, cardName);
                int cardCost; cardData >> cardCost;
                // skip to the next line
                cardData.ignore(10000, '\n');
                string cardDscr; getline(cardData, cardDscr);

                //Create card
                shared_ptr<Ritual> newRitual(new AddPlayerRitual(cardName, cardCost, playerModel.playerNumber, cardDscr, charges, activeCost, healthMod, magicMod, cardTrigger, targets));
                playerModel.deck.emplace_back(newRitual);
            } else if (target == "minion") {

                //Get modifiers
                //Get Ritual basics
                int activeCost; cardData >> activeCost;
                int charges; cardData >> charges;
                // skip to the next line
                cardData.ignore(10000, '\n');

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
                // skip to the next line
                cardData.ignore(10000, '\n');
                string target; getline(cardData, target);

                //Name and Cost and decsription
                string cardName; getline(cardData, cardName);
                int cardCost; cardData >> cardCost;
                // skip to the next line
                cardData.ignore(10000, '\n');
                string cardDscr; getline(cardData, cardDscr);;

                //Create card
                shared_ptr<Ritual> newRitual(new AddMinionRitual(cardName, cardCost, playerModel.playerNumber, cardDscr, charges, activeCost, attMod, defMod,actPerTurn, abilityCost, silenced, cardTrigger, target));
                playerModel.deck.emplace_back(newRitual);
            }
        } else if (ritualType == "move") {
            //Get Ritual basics
            int activeCost; cardData >> activeCost;
            int charges; cardData >> charges;

            // skip to the next line
            cardData.ignore(10000, '\n');

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
            // skip to the next line
            cardData.ignore(10000, '\n');
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Ritual> newRitual(new MoveRitual(cardName, cardCost, playerModel.playerNumber, cardDscr, charges, activeCost, cardTrigger, target, destination));
            playerModel.deck.emplace_back(newRitual);
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
            // skip to the next line
            cardData.ignore(10000, '\n');
            string attOperation; getline(cardData, attOperation);
            string defOperation; getline(cardData, defOperation);

            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            // skip to the next line
            cardData.ignore(10000, '\n');
            string cardDscr; getline(cardData, cardDscr);

            //Create card
            shared_ptr<Enchantment> newEnchantment(new AddEnchant(cardName, cardCost, playerModel.playerNumber, cardDscr, attMod, defMod, actPerTurn, abilityCost, attOperation, defOperation, silenced));
            playerModel.deck.emplace_back(newEnchantment);
        }
    }
}

void PlayerController::updateState(vector<Event> &events) {
    for (int i = 0; i < playerModel.minions.size(); ++i) {
      playerModel.minions.at(i)->update(events);
    }
    if (playerModel.ritual != nullptr) {
      playerModel.ritual->update(events);
    }
}

void PlayerController::drawCard(int numCards) {
    if (playerModel.deck.size() > 0) {
        for (int i = 0; i < numCards; ++i)
        {
            playerModel.hand.emplace_back(playerModel.deck.back());    //not sure if this actually works...
            playerModel.deck.pop_back();
        }
    }
    else throw out_of_range(getName());
}
Minion &PlayerController::minion(int i) {
    return *(playerModel.minions.at(i - 1));
}

const vector<shared_ptr<NonPlayer>> &PlayerController::getHand() const {
    return playerModel.hand;
}

void PlayerController::play(int i) {
    auto card = playerModel.hand.at(i - 1);

    if (card->getType() == Type::Spell) {
        card->cast();               //will update the board: no need to do in here
        playerModel.graveyard.emplace_back(card);
    }
    else if (card->getType() == Type::Ritual) {
        playerModel.ritual = dynamic_pointer_cast<Ritual>(card);
    }
    else if (card->getType() == Type::Minion) {
        playerModel.minions.emplace_back(dynamic_pointer_cast<Minion>(card));
    }
    else { }    //handle exception

    playerModel.hand.erase(playerModel.hand.begin() + (i - 1));     //remove card from hand
}

void PlayerController::play(int i, int p, char t) {
    auto card = playerModel.hand.at(i - 1);

    if (card->getType() == Type::Spell) {
        card->cast(p, t);               //will update the board: no need to do in here
        playerModel.graveyard.emplace_back(card);
    }
    else if (card->getType() == Type::Enchantment) {
        card->cast(p, t);
        playerModel.minions.at((int)(t - 1))->enchantments.emplace_back(dynamic_pointer_cast<Enchantment>(card));
    }
    else { }    //handle exception

    playerModel.hand.erase(playerModel.hand.begin() + (i - 1));     //remove card from hand
}

void PlayerController::use(int i) {
    playerModel.minions.at(i - 1)->cast();
}

void PlayerController::use(int i, int p, char t) {
    playerModel.minions.at(i - 1)->cast(p, t);
}

void PlayerController::attack(int i, int j) {
    playerModel.minions.at(i - 1)->attack(j, (i - 1));
}

void PlayerController::toGrave(bool Ritual, int minionIndex) {
  cout << "toGrave Minion: " << minionIndex << endl;
  if (Ritual) {
    playerModel.graveyard.emplace_back(playerModel.ritual);
    playerModel.ritual = nullptr;
  } else {
    playerModel.graveyard.emplace_back(playerModel.minions.at(minionIndex));
    cout << "Added to grave" << endl;
    playerModel.minions.erase(playerModel.minions.begin() + (minionIndex));
    cout << "Removed from board" << endl;
  }
}

 PlayerModel &PlayerController::getPlayerData() {
    return playerModel;
}

PlayerController::~PlayerController() {
    playerModel.deck.clear();
    playerModel.graveyard.clear();
    playerModel.hand.clear();
    playerModel.minions.clear();
}
