#include "minion.h"
#include "triggered.h"
#include <fstream>
#include "activated.h"

using namespace std;

Minion::Minion(string &name, int cost, int owner, int attack, int defence, vector<ifstream> &abilities):
        NonPlayer(name, cost, owner), att(attack), def(defence) {
    
    type = Type::Minion;
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

                    //Get modifiers
                    int modAtt;
                    int modDef;
                    abilities[i] >> modAtt;
                    abilities[i] >> modDef;

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
                }
            }
        }
    }
    //Construct concrete abilities here
};

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
