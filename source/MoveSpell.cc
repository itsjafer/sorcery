#include "spell.h"
#include "enchantment.h"
#include <iostream>

using namespace std;

MoveSpell::MoveSpell(string &cardName, int cost, int owner, string &description, string &moveSource, string &moveDestination, string &Target) :
        Spell(cardName, cost, owner, description), moveSource(moveSource), moveDestination(moveDestination), Target(Target) {}

void MoveSpell::updateState(vector<Event> &events) {

}

void MoveSpell::castCard() {

}

void MoveSpell::castCard(int p, int t) {
  if (t == -1) {
    if (moveSource == "field") {
      if (moveDestination == "grave") {
        if (Target == "minion:ritual" ) {
          board->players.at(p)->toGrave(true, -1);
        }
      }
    }
    //Move Ritual
  } else {
    vector<Event> eventsForTarget;
    //Move minion
    int targetCard = t;
    if (moveSource == "field") {
      if (moveDestination == "grave") {
        if (Target == "minion" || Target == "minion:ritual" ) {
          eventsForTarget.emplace_back(Event::minionDied);
          board->players.at(p)->toGrave(false, targetCard - 1);
          board->updateBoard(eventsForTarget);
        } else if (Target == "enchantment") {
          board->players.at(p)->minion(t).enchantments.back()->unCast(p, t);
          board->players.at(p)->minion(t).enchantments.pop_back();
        }
      } else if (moveDestination == "hand") {
        if (Target == "minion" || Target == "minion:ritual" ) {
          eventsForTarget.emplace_back(Event::minionDied);
          board->players.at(p)->toHand(targetCard - 1);
        }
      }
    }
  }
}
