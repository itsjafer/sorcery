#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
    virtual void notifyDisplay(Subject &whoNotified) = 0;
public:
    void notify(Subject &whoNotified); // created to avoid public virtual function
    virtual ~Observer() = 0;
};

#endif
