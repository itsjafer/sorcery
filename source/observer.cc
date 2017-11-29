#include "observer.h"

void Observer::notify(Subject &whoFrom, State command) {
  notifyDisplay(whoFrom, command);
}