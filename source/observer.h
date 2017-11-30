#ifndef OBSERVER_H
#define OBSERVER_H
#include "state.h"

class Subject;

class Observer {
    virtual void notifyDisplay(Subject &whoNotified, State command, int minion = 0) = 0;
public:
    void notify(Subject &whoNotified, State command, int minion = 0); // created to avoid public virtual function
    virtual ~Observer() = default;
};

#endif
