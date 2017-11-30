#include "nonplayer.h"

const Type NonPlayer::getType() const {
  return Type::Spell;
}

std::string NonPlayer::getDescription() {
  return description;
}

int NonPlayer::getCost() {
  return cost;
}

void NonPlayer::cast() {
  castCard();
}
void NonPlayer::cast(int p, char t) {
  castCard(p,t);
}