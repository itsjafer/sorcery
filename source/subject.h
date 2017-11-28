#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
    std::vector<Observer *> observers;
public:
    void attach(Observer *ob); // attaches an observer to this subject
    void notifyObservers(); // alerts all observers
    // virtual Info getInfo() const = 0;
    virtual ~Subject() = 0;
};

#endif
