#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "boardmodel.h"
#include "invalidmove.h"
#include "state.h"

class PlayerController;
class PlayerModel;
class Observer;


class BoardController {
    std::vector<std::shared_ptr<Observer>> observers;
    BoardModel boardData;
    unsigned int currentPlayer;
    bool gameOver;
    std::ifstream *init = nullptr;
    void attack(std::stringstream &ss);
    void play(std::stringstream &ss);
    void use(std::stringstream &ss);
    void discard(std::stringstream &ss);
    void draw();
public:
    BoardController(std::vector<std::string> &players, std::vector<std::unique_ptr<std::ifstream>> &data, std::vector<std::shared_ptr<Observer>> &observers, bool testingMode);
    void preTurn();
    void execute();
    void postTurn();
    bool gameEnded();
    int whoWon();
    void switchPlayers();   

    void attach(std::shared_ptr<Observer> o);  
    void notifyObservers(State command, int minion = 0);
    void notifyObservers(std::string message);
    
    void setInit(std::ifstream *init);
    std::vector<PlayerModel> getPlayerInfos() const;
    int getCurrentPlayer();
    
    ~BoardController();

    // operator overload to print out the board
    friend std::ostream &operator<<(std::ostream &out, const BoardController &board);

};

#endif
