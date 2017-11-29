#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "state.h"
#include <vector>
#include <memory>

class Player;

struct Info {
  std::vector<std::string> name;
  std::vector<int> health;
  std::vector<int> magic;
  std::vector<std::string> ritual;
  std::vector<std::vector<std::string>> minions;
  std::vector<std::string> graveyard;
};

#endif