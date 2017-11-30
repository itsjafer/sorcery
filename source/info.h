#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "state.h"
#include <vector>
#include <memory>

struct Info {
  std::string name;
  int health;
  int magic;
  
  std::shared_ptr<Ritual> ritual;
  std::shared_ptr<NonPlayer> graveyard;
  std::vector<std::shared_ptr<Minion>> minions; // stores ALL information about minions
  std::vector<std::shared_ptr<NonPlayer>> hand;
};

#endif