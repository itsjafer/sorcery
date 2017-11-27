#include "minion.h"
#include "triggered.h"
#include <fstream>
#include "event.h"

class Ability;
class Enchantment;
using namespace std;



Minion::Minion(string &name, int cost, int owner, int attack, int defence, vector<ifstream> &abilities):
        NonPlayer(name, cost, owner), att(attack), def(defence) {

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
                    if (tempLine == "any leave play") {
                        event = Event::minionDied;
                    }
                    AdderTriggered newAddTrig = new AdderTriggered();
                    this->abilities.emplace_back(newAddTrig);
                }

            } else if (tempLine == "activated") {

                //For activated abilities
                getline(abilities[i], tempLine);
                if (tempLine == "add") {
                    //Instantiate concrete activateAddAbility object
                } else if (tempLine == "summon") {
                    //Instantiate concrete activateSummonAbility object
                }
            }
        }
    }
    //Construct concrete abilities here
};

void Minion::attack(int i = 0);

Minion::~Minion(){

};

