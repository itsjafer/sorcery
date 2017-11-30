#include "boardmodel.h"
#include "minion.h"
#include "nonplayer.h"
#include "player.h"
#include "subject.h"
#include "state.h"
#include "info.h"
#include <iostream>

BoardModel::BoardModel(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data) {
  std::cout << "BoardModel.cc: Players are being initialized in the constructor." << std::endl;
  for (unsigned int i = 0; i < players.size(); ++i) {
    std::cout << "BoardModel.cc: Player " << i << " has been created (as a unique pointer: this might need to change)" << std::endl;
    this->players.emplace_back(std::shared_ptr<Player>(new Player(players[i], data[i])));
  }
}

void BoardModel::displayBoard() {
  notifyObservers(State::printBoard);
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

std::vector<Info> BoardModel::getInfo() const {
  std::vector<Info> playerInfos;
  for (unsigned int i = 0; i < players.size(); ++i) {
    Info myInfo;
    // add the name, magic, and health of the player
    myInfo.name = players[i]->getName();
    myInfo.magic = players[i]->magic;
    myInfo.health = players[i]->health;

    // add the name of the player's ritual
    // if the player has a ritual:
    // myInfo.ritual = players[i].ritual;

    // add the player's minions
    for (unsigned int j = 0; j < players[i]->minions.size(); ++j) {
      myInfo.minions.emplace_back(players[i]->minions[j]);
    }

    // add the player's hands
    for (unsigned int j = 0; j < players[i]->hand.size(); ++j) {
      myInfo.hand.emplace_back(players[i]->hand[j]);
    }

    if (!players[i]->graveyard.empty()) {
      myInfo.graveyard = players[i]->graveyard.front();
    }
    
    playerInfos.emplace_back(myInfo);
  }
  return playerInfos;
}