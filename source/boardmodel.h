#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <vector>
#include <string>
#include <fstream>
#include "player.h"

class BoardModel {
public:
    std::vector<Player> players;
    BoardModel(std::vector<std::unique_ptr<std::fstream>> &data);
    void updateBoard();
    ~BoardModel();
};

#endif
