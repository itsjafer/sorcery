#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "state.h"
#include "observer.h"

struct Info;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> o);  
    void notifyObservers(State command);
    virtual Info getInfo() const = 0;
    virtual ~Subject() = 0;
};

#endif
