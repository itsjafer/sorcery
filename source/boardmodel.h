#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <vector>
#include <string>
#include <fstream>
#include "event.h"
#include <memory>

class Player;

class BoardModel {
    const int fieldSize = 5;
public:
    const bool testingMode;
    int getFieldSize();
    int getMagic(int player); // returns the magic of the given player
    void setMagic(int player, int newValue); 
    int getHealth(int player); // returns the health of the given player
    bool isDeckEmpty(int player); // returns if the deck is empty for the given player
    std::vector<std::unique_ptr<Player>> players;
    BoardModel(std::vector<std::string> players, std::vector<std::unique_ptr<std::ifstream>> &data, bool testingMode);
    void updateBoard(std::vector<Event> events);
    ~BoardModel();
};

#endif
