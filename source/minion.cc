#include "minion.h"
#include "triggered.h"
#include <fstream>
#include "event.h"
#include "activated.h"

class Ability;
class Enchantment;
using namespace std;



Minion::Minion(string &name, int cost, int owner, int attack, int defence, vector<ifstream> &abilities):
        NonPlayer(name, cost, owner), att(attack), def(defence), type(Type::Minion) {

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
                    AdderTriggered newAddTrig{event, modAtt, modDef, target, descriptor};
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

                    //Create ability, add it to the back
                    AdderActive newAddAct{costAmount, modAtt, modDef, target, descriptor};
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

void Minion::attack(int i = 0) {
    
}

Minion::~Minion(){

};

