#include "observer.h"

void Observer::notify(Subject &whoFrom, State command, int minion) {
  notifyDisplay(whoFrom, command, minion);
}