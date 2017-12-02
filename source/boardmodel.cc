#include "boardmodel.h"
#include "minion.h"
#include "nonplayer.h"
#include "player.h"
#include <iostream>

BoardModel::BoardModel(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data) {
  std::cout << "BoardModel.cc: Players are being initialized in the constructor." << std::endl;
  for (unsigned int i = 0; i < players.size(); ++i) {
    std::cout << "BoardModel.cc: Player " << i << " has been created." << std::endl;
    this->players.emplace_back(std::unique_ptr<Player>(new Player(players[i], data[i])));
    std::cout << "BoardModel.cc: Player " << i << " has " << this->players[i]->deck.size() << " cards in their deck." << std::endl;
  }
}

bool BoardModel::isDeckEmpty(int player) {
  return (players[player])->deck.empty();
}

void BoardModel::updateBoard(std::vector<Event> events) {
  // loop through every non-player in each player's minions, ritual(s)
  // for each card, let it know that the events have occurred
  for (unsigned int i = 0; i < players.size(); ++i) {
      std::cout << "BoardModel.cc: Player " << i << " has been alerted with an event." << std::endl;
      players[i]->update(events);
  }

}

int BoardModel::getMagic(int player) {
  return players[player]->magic;
}

void BoardModel::setMagic(int player, int newValue) {
  players[player]->magic = newValue;
} 

int BoardModel::getHealth(int player) {
  return players[player]->health;
}

void BoardModel::setHealth(int player, int newValue) {
  players[player]->health = newValue;
}

BoardModel::~BoardModel() {
  players.clear();
}
