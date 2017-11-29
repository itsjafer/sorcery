#include "card.h"

Card::Card(std::string &name) {
  this->name = name;
}

void Card::setBoard(BoardModel *board) {

}
std::string & Card::getName() {
  return name;
}

void Card::update(std::vector<Event> &events) {
  // implementation needed!!!!
}