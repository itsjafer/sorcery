#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
    virtual void notifyDisplay(Subject &whoNotified) = 0;
public:
    void notify(Subject &whoNotified);
    virtual ~Observer() = 0;
};

#endif
