#include "nonplayer.h"

const Type NonPlayer::getType() const {
  return Type::Spell;
}

void NonPlayer::cast() {
  castCard();
}
void NonPlayer::cast(int p, char t) {
  castCard(p,t);
}