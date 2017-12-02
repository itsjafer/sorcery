#include "minion.h"
#include "triggered.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "activated.h"

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
    cout << "minion.cc: I have " << abilities.size() << " abilities" << endl;
    return (abilities.size() != 0);
}

Type Minion::getAbilityType(int i) {
    return abilities[i]->getType();
}

int Minion::getAbilityCost(int i) {
    return abilities[i]->getCost();
}

void Minion::updateState(vector<Event> &events) {

}

void Minion::castCard() {

}

void Minion::castCard(int p, char t) {

}

void Minion::attack(int i) {

}

Minion::~Minion(){
    abilities.clear();
    enchantments.clear();
};
