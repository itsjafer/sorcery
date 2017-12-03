#include "card.h"
#include <iostream>

BoardModel *Card::board;

Card::Card(std::string &name): name{name} { }

BoardModel *Card::board;

void Card::setBoard(BoardModel *board) {
  this->board = board;
}
std::string & Card::getName() {
  return name;
}

void Card::update(std::vector<Event> &events) {
  updateState(events);
}
