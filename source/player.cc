#include "player.h"
#include "minion.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

Player::Player(string &name, ifstream &deck): Card{name} {
    string cardFile;
    while (getline(deck, cardFile)) {
        ifstream cardData{cardFile};
        addCard(cardData);
    }
}

void Player::updateState(std::vector<Event> &events) {
    // we're going to update the minions and the ritual
    for (int i = 0; i < minions.size(); ++i) {
      minions[i]->update(events);
    }

    //ritual->update(events);
}