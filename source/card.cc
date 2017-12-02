#include "card.h"
#include <iostream>

Card::Card(std::string &name): name{name} { }

BoardModel *Card::board;

void Card::setBoard(BoardModel *board) {

}
std::string & Card::getName() {
  return name;
}

void Card::update(std::vector<Event> &events) {
  updateState(events);
}
