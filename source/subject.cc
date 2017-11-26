#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *o) {
  observers.push_back(o);
}

void Subject::notifyObservers() {
  for (unsigned int i = 0; i < observers.size(); i++) {
    observers[i]->notify(*this);
  }
}

Subject::~Subject(){ 
  
}