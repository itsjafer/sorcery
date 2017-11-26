#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "subject.h"
#include "boardmodel.h"

class BoardController: public Subject {
    BoardModel data;
public:
    BoardController(std::vector<std::fstream> &data);
    void preTurn();
    void execute();
    void postTurn();
    bool gameEnded();
    int whoWon();
    ~BoardController();
};

#endif
