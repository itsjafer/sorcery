#include "enchantment.h"

using namespace std;

Enchantment::Enchantment(string &name, int cost, int owner, std::string &description): NonPlayer{name, cost, owner, description} {
  this->type = Type::Enchantment;
}
