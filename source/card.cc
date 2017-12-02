#include "card.h"

BoardModel *Card::board;

Card::Card(std::string &name): name{name} { }

void Card::setBoard(BoardModel *board) {
  this->board = board;
}
std::string & Card::getName() {
  return name;
}

void Card::update(std::vector<Event> &events) {
  // implementation needed!!!!
}
