#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "subject.h"
#include "boardmodel.h"
#include "invalidmove.h"

class Player;

class BoardController: public Subject {
    BoardModel boardData;
    unsigned int currentPlayer;
    bool gameOver;
    void attack(std::stringstream &ss);
    void play(std::stringstream &ss);
    void use(std::stringstream &ss);
    void discard(std::stringstream &ss);
    void draw();
public:
    BoardController(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data, bool testingMode);
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
