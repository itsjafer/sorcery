#include "boardmodel.h"
#include "minion.h"
#include "nonplayer.h"
#include "playercontroller.h"
#include "state.h"
#include <iostream>

BoardModel::BoardModel(std::vector<std::string> &players, std::vector<std::unique_ptr<std::ifstream>> &data, bool testingMode): testingMode{testingMode} {

  for (unsigned int i = 0; i < players.size(); ++i) {
    this->players.emplace_back(std::unique_ptr<PlayerController>(new PlayerController(players[i], data[i], i)));
    if (!testingMode) this->players.at(i)->shuffleDeck();
  }
  this->players.at(0)->setBoard(this);
}

bool BoardModel::isDeckEmpty(int player) {
  return players[player]->getPlayerData().deck.empty();
}

void BoardModel::updateBoard(std::vector<Event> events) {
  // loop through every non-player in each player's minions, ritual(s)
  // for each card, let it know that the events have occurred
  for (unsigned int i = 0; i < players.size(); ++i) {
      this->players.at(i)->update(events);
  }
}

void BoardModel::updateBoard(std::vector<Event> events, int player) {
    this->players.at(player)->update(events);
}

int BoardModel::getFieldSize() {
  return fieldSize;
}

int BoardModel::getMagic(int player) {
  return players[player]->getPlayerData().magic;
}

void BoardModel::setMagic(int player, int newValue) {
  players[player]->playerModel.magic = newValue;
}

int BoardModel::getHealth(int player) {
  return players[player]->getPlayerData().health;
}

void BoardModel::setHealth(int player, int newValue) {
  players[player]->playerModel.health = newValue;
}

BoardModel::~BoardModel() {
  players.clear();
}
