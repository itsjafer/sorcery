#include "observer.h"

void Observer::notify(BoardController &whoFrom, State command, int minion) {
  notifyDisplay(whoFrom, command, minion);
}

void Observer::notify(std::string &message) {
  notifyDisplay(message);
}
