#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "subject.h"
#include "boardmodel.h"
#include "textdisplay.h"

class BoardController: public Subject {
    BoardModel boardData;
    unsigned int currentPlayer;
    bool gameOver;
public:
    BoardController(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data);
    void preTurn();
    void execute();
    void postTurn();
    bool gameEnded();
    int whoWon();
    void switchPlayers();    
    ~BoardController();

    // operator overload to print out the board
    friend std::ostream &operator<<(std::ostream &out, const BoardController &board);

};

#endif
