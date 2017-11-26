#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "subject.h"
#include "boardmodel.h"
#include "textdisplay.h"

class BoardController: public Subject {
    TextDisplay *td; // The text display

    BoardModel data;
public:
    BoardController(std::vector<std::fstream> &data);
    void preTurn();
    void execute();
    void postTurn();
    bool gameEnded();
    int whoWon();
    ~BoardController();

    // operator overload to print out the board
    friend std::ostream &operator<<(std::ostream &out, const BoardController &board);

};

#endif
