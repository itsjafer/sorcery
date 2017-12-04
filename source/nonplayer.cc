#include "nonplayer.h"

using namespace std;

NonPlayer::NonPlayer(string &name, int cost, int owner, string description): Card{name}, cost{cost}, owner{owner}, description{description} { }

int NonPlayer::getCost() {
  return cost;
}

void NonPlayer::cast() {
  castCard();
}

void NonPlayer::cast(int p, int t) {
  castCard(p,t);
}

void NonPlayer::setCost(int cost) {
  this->cost = cost;
}

int NonPlayer::getOwner() {
  return owner;
}

string NonPlayer::getDescription() {
  return description;
}

void NonPlayer::setOwner(int owner) {
  this->owner = owner;
}

const Type NonPlayer::getType() const {
  return type;
}
