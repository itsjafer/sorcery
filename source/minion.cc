#include "minion.h"
#include "triggered.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "activated.h"
#include "playercontroller.h"

using namespace std;

Minion::Minion(string &name, int cost, int owner, int attack, int defence, vector<ifstream> &abilities):
        NonPlayer(name, cost, owner), att(attack), def(defence) {

    type = Type::Minion;
    // cout << "Minion.cc: Initializing minion, " << name << endl;
    std::string tempLine;

    //Goes through all ability files and instantiates abilities
    for (unsigned int i = 0; i < abilities.size(); i++) {

        if(abilities[i].is_open()) {

            getline(abilities[i], tempLine);

            if (tempLine == "triggered") {

                //For triggered abilities
                getline(abilities[i], tempLine);
                if (tempLine == "add") {
                    //Instantiate concrete triggerAddAbility object
                    Event event;
                    getline(abilities[i], tempLine);
                    //Get the trigger event
                    if (tempLine == "any leave play") {
                        event = Event::minionDied;
                    }

                    //Get modifiers
                    int modAtt;
                    int modDef;
                    abilities[i] >> modAtt;
                    abilities[i] >> modDef;

                    // skip to the next line
                    abilities[i].ignore(10000, '\n');

                    //Get target
                    std::string target;
                    getline(abilities[i], target);

                    //Get description
                    std::string descriptor;
                    getline(abilities[i], descriptor);

                    //Create ability, add it to the back
                    shared_ptr<Ability> newAddTrig{new AdderTriggered(event, modAtt, modDef, target, descriptor)};
                    this->abilities.emplace_back(newAddTrig);
                }

            } else if (tempLine == "activated") {

                //For activated abilities
                getline(abilities[i], tempLine);
                if (tempLine == "add") {
                    //Instantiate concrete activateAddAbility object
                    int costAmount;
                    abilities[i] >> costAmount;

                    // skip to the next line
                    abilities[i].ignore(10000, '\n');

                    //Get modifiers
                    int modAtt;
                    int modDef;
                    abilities[i] >> modAtt;
                    abilities[i] >> modDef;

                    // skip to the next line
                    abilities[i].ignore(10000, '\n');

                    //Get target
                    std::string target;
                    getline(abilities[i], target);

                    //Get description
                    std::string descriptor;
                    getline(abilities[i], descriptor);
                    string name = "none";

                    //Create ability, add it to the back
                    shared_ptr<Ability> newAddAct{new AdderActive(name, costAmount, -1, descriptor, modAtt, modDef, target)};
                    this->abilities.emplace_back(newAddAct);

                } else if (tempLine == "summon") {
                    //Instantiate concrete activateSummonAbility object
                    //Do later
                    //Instantiate concrete activateSummonAbility object
                    int costAmount;
                    abilities[i] >> costAmount;
                    int summonAmount;
                    abilities[i] >> summonAmount;

                    // skip to the next line
                    abilities[i].ignore(10000, '\n');

                    std::string summonMinion;
                    getline(abilities[i], summonMinion);

                    //Get description
                    std::string descriptor;
                    getline(abilities[i], descriptor);
                    string name = "none";

                    //Create ability, add it to the back
                    shared_ptr<Ability> newSumAct{
                            new SummonActive(name, costAmount, -1, descriptor, summonAmount, summonMinion)};
                    this->abilities.emplace_back(newSumAct);
                }
            }
        }
    }

    //Construct concrete abilities here
    // cout << "Minion.cc: Found the minion, " << name << " with cost, " << cost
    //     << " and attack/defense of " << att << "/" << def  << " and " << this->abilities.size() << " abilities" << endl;
    // for (int i = 0; i < this->abilities.size(); ++i) {
    //     cout << "Ability " << i << ": " << this->abilities[i]->getDescription() << endl;
    // }
    // cout << endl;
    // cout << endl;
};

int Minion::getAttack() {
    return att;
}

int Minion::getDefence() {
    return def;
}

bool Minion::hasAbility() {
    return (abilities.size() != 0);
}

Type Minion::getAbilityType(int i) {
    return abilities[i]->getType();
}

int Minion::getAbilityCost(int i) {
    return abilities[i]->getCost();
}

void Minion::updateState(vector<Event> &events) {
  for (int i = 0; i < abilities.size(); ++i) {
    abilities[i]->update(events);
  }
}

void Minion::castCard() {
  abilities[0]->cast();
}

void Minion::castCard(int p, char t) {
  abilities[0]->cast(p, t);
}

void Minion::attack(int i, int me) {
  //If the minion can attack
  if (canAttack) {

    //Find oponent value
    int opponent;
    if (this->getOwner() == 0) {
      opponent = 1;
    } else if (this->getOwner() == 1) {
      opponent = 0;
    }

    //Attack functionality
    if (i == 0) {
      cout << "minion attacking player" << endl;
      //Attack a person
      vector<Event> EventsForA;
      vector<Event> AllEvents;

      //Damage target player
      board->setHealth(opponent, board->getHealth(opponent) - this->att);

      //Set the events only if damage was dealth ( > 0)
      if (this->att > 0) {
        EventsForA.emplace_back(Event::minionDealtDamage);
        AllEvents.emplace_back(Event::playerTookDamage);
      }

      //Update minion sates
      this->updateState(EventsForA);
      board->updateBoard(AllEvents);

    }
    else {

      //Attack the ith minions
      vector<Event> EventsForA;
      vector<Event> EventsForB;
      vector<Event> AllEvents;

      //Damage target minion
      board->players.at(opponent)->minion(i).def -= this->att;

      //Set the events only if damage was dealth ( > 0)
      if (this->att > 0) {
        EventsForA.emplace_back(Event::minionDealtDamage);
        EventsForB.emplace_back(Event::minionTookDamage);
      }

      //Damage current minion
      this->def -= board->players.at(opponent)->minion(i).att;

      //Set the events only if damage was dealth ( > 0)
      if (board->players.at(opponent)->minion(i).att > 0) {
        EventsForB.emplace_back(Event::minionDealtDamage);
        EventsForA.emplace_back(Event::minionTookDamage);
      }

      //Create unique vector for all events
      if ((this->att > 0) || (board->players.at(opponent)->minion(i).att > 0)) {
        AllEvents.emplace_back(Event::minionDealtDamage);
        AllEvents.emplace_back(Event::minionTookDamage);
      }

      //Create unique vector for all events
      if ((this->def <= 0) || (board->players.at(opponent)->minion(i).def <= 0)) {
        AllEvents.emplace_back(Event::minionDied);
        board->updateBoard(AllEvents);
      }

      //If this minion died
      if (this->def <= 0) {
        //Move to graveyard
        EventsForA.emplace_back(Event::minionDied);
        board->players.at(this->getOwner())->toGrave(false, me);
      }

      //Update this minion with EventsForA
      this->updateState(EventsForA);

      //If other minion died
      if (board->players.at(opponent)->minion(i).def <= 0)  {
        //Move to graveyard
        EventsForB.emplace_back(Event::minionDied);
        board->players.at(opponent)->minion(i).updateState(EventsForB);
        board->players.at(opponent)->toGrave(false, i - 1);
      } else {
        board->players.at(opponent)->minion(i).updateState(EventsForB);
      }
    }
  }
}

Minion::~Minion(){
    abilities.clear();
    enchantments.clear();
};
