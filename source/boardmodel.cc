#include "boardmodel.h"
#include "minion.h"
#include "nonplayer.h"
#include <iostream>

BoardModel::BoardModel(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data) {
  std::cout << "BoardModel.cc: Players are being initialized in the constructor." << std::endl;
  for (unsigned int i = 0; i < players.size(); ++i) {
    std::cout << "BoardModel.cc: Player " << i << " has been created (as a unique pointer: this might need to change)" << std::endl;
    this->players.emplace_back(std::unique_ptr<Player>(new Player(players[i], data[i])));
  }
}

bool BoardModel::isDeckEmpty(int player) {
  return (players[player])->deck.size();
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

BoardModel::~BoardModel() {
  
}