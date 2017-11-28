#include "observer.h"

void Observer::notify(Subject &whoFrom) {
  notifyDisplay(whoFrom);
}