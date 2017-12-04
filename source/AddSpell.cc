#include "spell.h"
#include <iostream>

using namespace std;

AddSpell::AddSpell(std::string &cardName, int cost, int owner, string &description, int attMod, int defMod, string attOperation, string defOperation, string &Target):
        Spell(cardName, cost, owner, description), attMod(attMod), defMod(defMod), attOperation(attOperation), defOperation(defOperation), Target(Target) {}

void AddSpell::updateState(vector<Event> &events) {

}

void AddSpell::castCard() {
  if (Target == "all minions") {
    for (int i = 0; i < board->players.size(); ++i) {
      for (int j = board->players.at(i)->numMinions(); j > 0; --j) {
        vector<Event> eventsForTarget;
        if (attOperation == "+") {
          board->players.at(i)->minion(j).att += attMod;
        }
        if (defOperation == "+") {
          board->players.at(i)->minion(j).def += defMod;
        }
        if (board->players.at(i)->minion(j).def <= 0) {
          eventsForTarget.emplace_back(Event::minionDied);
          board->players.at(i)->toGrave(false, j - 1);
          board->updateBoard(eventsForTarget);
        }
      }
    }
  }

}

void AddSpell::castCard(int p, int t) {

}
