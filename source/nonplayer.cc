#include "nonplayer.h"

using namespace std;

NonPlayer::NonPlayer(string &name, int cost, int owner, string description): Card{name}, cost{cost}, owner{owner}, description{description} { }

std::string NonPlayer::getDescription() {
  return description;
}

int NonPlayer::getCost() {
  return cost;
}

void NonPlayer::cast() {

}

void NonPlayer::cast(int p, char t) {

}

int NonPlayer::getCost() {

}

void NonPlayer::setCost(int cost) {

}

int NonPlayer::getOwner() {

}

void NonPlayer::setOwner(int owner) {
    
}

const Type NonPlayer::getType() const {

}
