#include "subject.h"
#include "observer.h"
#include <memory>

void Subject::attach(std::shared_ptr<Observer> o) {
  observers.push_back(o);
}

void Subject::notifyObservers(State command, int player, int minion) {
  for (unsigned int i = 0; i < observers.size(); i++) {
    observers[i]->notify(*this, command, player, minion);
  }
}

Subject::~Subject(){ 
  
}