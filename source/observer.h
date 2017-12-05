#ifndef OBSERVER_H
#define OBSERVER_H
#include "state.h"
#include <string>

class BoardController;

class Observer {
    virtual void notifyDisplay(BoardController &whoNotified, State command, int minion) = 0;
    virtual void notifyDisplay(std::string &message) = 0;
    
public:
    void notify(BoardController &whoFrom, State command, int minion = 0); // created to avoid public virtual function
    void notify(std::string &message); // created to avoid public virtual function
    
    virtual ~Observer() = default;
};

#endif
