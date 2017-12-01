#include "observer.h"

void Observer::notify(Subject &whoFrom, State command, int player, int minion) {
  notifyDisplay(whoFrom, command, minion);
}