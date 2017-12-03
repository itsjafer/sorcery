#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include "event.h"
#include "invalidmove.h"
#include "boardmodel.h"

class Card {
    std::string name;
    virtual void updateState(std::vector<Event> &events) = 0;
protected:
    static BoardModel *board;
public:
    Card(std::string &name);
    void setBoard(BoardModel *board);
    std::string &getName();
    void update(std::vector<Event> &events);
    virtual ~Card() = default;
};

#endif
