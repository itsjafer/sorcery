#include "boardmodel.h"

BoardModel::BoardModel(std::vector<std::string> players, std::vector<std::ifstream> &data) {
  for (int i = 0; i < players.size(); ++i) {
    Player p(players[i], data[i]);
  }
}

bool BoardModel::isDeckEmpty(int player) {
  return players[player].deck.size();
}

void BoardModel::updateBoard(std::vector<Event> events) {
  // loop through every non-player in each player's minions, ritual(s)
  // for each card, let it know that the events have occurred
  for (int i = 0; i < players.size(); ++i) {
      players[i].update(events);
  }

}

int BoardModel::getMagic(int player) {
  return players[player].magic;
}

void BoardModel::setMagic(int player, int newValue) {
  players[player].magic = newValue;
}

int BoardModel::getHealth(int player) {
  return players[player].health;
}

BoardModel::~BoardModel() {
  
}