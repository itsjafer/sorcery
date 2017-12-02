#include "nonplayer.h"

using namespace std;

NonPlayer::NonPlayer(string &name, int cost, int owner, string description): Card{name}, cost{cost}, owner{owner}, description{description} { }

void NonPlayer::cast() {

}

void NonPlayer::cast(int p, char t) {

}

int NonPlayer::getCost() {

}

void NonPlayer::setCost(int cost) {

}

int NonPlayer::getOwner() {
  return owner;
}

void NonPlayer::setOwner(int owner) {
    
}

const Type NonPlayer::getType() const {

}

std::string NonPlayer::getDescription() {
  return description;
}