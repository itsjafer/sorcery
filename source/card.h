#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include "event.h"

class BoardModel;

class Card {
    static BoardModel *board;
    std::string name;
    virtual void updateState(std::vector<Event> &events) = 0;
public:
    Card(std::string &name);
    void setBoard(BoardModel *board);
    std::string &getName();
    void update(std::vector<Event> &events);
    virtual ~Card() = 0;
};

#endif
