#ifndef OBSERVER_H
#define OBSERVER_H
#include "state.h"

class BoardController;

class Observer {
    virtual void notifyDisplay(BoardController &whoNotified, State command, int minion) = 0;
public:
    void notify(BoardController &whoFrom, State command, int minion = 0); // created to avoid public virtual function
    virtual ~Observer() = default;
};

#endif
