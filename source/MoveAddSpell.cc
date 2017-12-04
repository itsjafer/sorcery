#include "spell.h"
#include <iostream>

using namespace std;


MoveAddSpell::MoveAddSpell(string &cardName, int cost, int owner, string &description, int attMod, int defMod, string attOperation, string defOperation,
                           string &moveSource, string &moveDestination, string &Target):
        Spell(cardName, cost, owner, description), attMod(attMod), defMod(defMod), moveSource(moveSource), moveDestination(moveDestination), attOperation(attOperation), defOperation(defOperation), Target(Target){}

void MoveAddSpell::updateState(vector<Event> &events) {

}

void MoveAddSpell::castCard() {
  if (moveSource == "grave") {
    if (moveDestination == "field") {
      if (Target == "minion") {

        board->players.at(this->getOwner())->resurrectLast();
        if (attOperation == "+") {
          board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).att += attMod;
        } else if (attOperation == "=") {
          board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).att = attMod;
        }

        if (defOperation == "+") {
          board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).def += defMod;
        } else if (defOperation == "=") {
          board->players.at(this->getOwner())->minion(board->players.at(this->getOwner())->numMinions()).def = defMod;
        }
      }
    }
  }
}

void MoveAddSpell::castCard(int p, int t) {

}
