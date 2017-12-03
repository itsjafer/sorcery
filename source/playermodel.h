#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "state.h"
#include <vector>
#include <memory>

class NonPlayer;
class Ritual;
class Minion;

class PlayerModel {
public:
  std::string name;
  int playerNumber;
  int health = 20;
  int magic = 3;

  std::vector<std::shared_ptr<NonPlayer>> deck;
  std::shared_ptr<Ritual> ritual;
  std::vector<std::shared_ptr<NonPlayer>> graveyard;
  std::vector<std::shared_ptr<Minion>> minions;
  std::vector<std::shared_ptr<NonPlayer>> hand;
  PlayerModel(std::string name, int playerNumber);
  ~PlayerModel();

};

#endif
