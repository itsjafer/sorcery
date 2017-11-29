#include "textdisplay.h"
#include "ascii_graphics.h"
#include "subject.h"
#include "player.h"
#include "info.h"
#include <iostream>

// constructor
TextDisplay::TextDisplay() {
  // initialize the theDisplay
  int cardsPerRow = 5;
  // start by creating an empty display with just templates

  std::cout << "textdisplay.cc: Initializing TextDisplay." << std::endl;
  // drawing an empty hand and field for all players
  for (int i = 0; i < 2; ++i) {
    std::vector<card_template_t> temp;
    for (int j = 0; j < cardsPerRow; ++j) {
      temp.emplace_back(CARD_TEMPLATE_EMPTY);
    }
    fields.emplace_back(temp);
    hands.emplace_back(temp);
  }
}

TextDisplay::~TextDisplay() {

}

void TextDisplay::notifyDisplay(Subject &whoNotified, State command) {
  std::cout << "textdisplay.cc: I have been notified." << std::endl;
  // what to do when I'm notified
  // im thinking that a subject might give me info (as to what has been requested)

  // notified of printBoard
  if (command == State::printBoard) {
    printBoard(whoNotified);
  }
}


// needs all information about a player
void TextDisplay::printBoard (Subject &whoNotified) {
  std::cout << "textdisplay.cc: I'm going to print now." << std::endl;
  Info boardInfo = whoNotified.getInfo();

  // loop through each player
  for (int i = 0; i < 2; ++i) { // consider replacing 2 with a variable
    
    // update player one's hand

    // the first card is the ritual
    // check if player one has a ritual
    // this code is not yet implemented so for now we have an empty card
    if (boardInfo.ritual[i] == "") {
      hands[i][0] = CARD_TEMPLATE_BORDER;
    }
    
    // note that the second and fourth cards of a hand are always empty
    // this is due to the graphics described in project requirements

    // the third card is the player card
    hands[i][2] = display_player_card(1, boardInfo.name[i], boardInfo.health[i], boardInfo.magic[i]);

    // the last card is the top of the graveyard
    // this code is not yet implemented so for now we have an empty card
    if (boardInfo.graveyard[i] == "") {
      hands[i][4] = CARD_TEMPLATE_BORDER;    
    }

    // we're going to fill our minion spots with an empty template
    for (int j = 0; j < 5; ++j) {
      fields[i][j] = CARD_TEMPLATE_BORDER;
    }

    // if neither players have any minions, we're done
    if (boardInfo.minions.empty() || boardInfo.minions[i].empty()) {
      continue;
    }

    // if we have minions, let's populate our field
    for (unsigned int j = 0; j < boardInfo.minions[i].size(); ++j) {
      // print out the minions here./sor
      // minions haven't been implemented yet so nothing is here yet
    }
  }
}
void TextDisplay::printHand(int currentPlayer, std::ostream &out, const TextDisplay &td) const {
  // print out the hand by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < td.hands[currentPlayer].size(); ++j) {
      // print the i'th line of each of the cards in the hand
      out << td.hands[currentPlayer][j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }
}

void TextDisplay::printField(int currentPlayer, std::ostream &out, const TextDisplay &td) const {
  // print out the field by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < td.fields[currentPlayer].size(); ++j) {
      out << td.fields[currentPlayer][j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {

  int currentPlayer = 0;
  int cardWidth = 33; // change this later maybe

  // draw the top left border
  out << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  unsigned int width = cardWidth * td.hands[currentPlayer].size();
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

  td.printHand(currentPlayer, out, td);
  td.printField(currentPlayer, out, td);
  

  // print out the logo
  for (unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) {
    out << CENTRE_GRAPHIC[i] << std::endl;
  }

  // increment to the next player
  currentPlayer++;

  td.printField(currentPlayer, out, td);
  td.printHand(currentPlayer, out, td);

  // draw the bottom left border
  out << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;

  return out;
}
// display the board
// operator overload with board

// display the hand
// operator overload with a vector of non-players

// inspect a minion
// - show the minion then show his enchantments
// operator overload with minion

// display a single card
// operator overload with a card

// display a minion
// operator overload with a minion

// display an enchantment
// operator overload with an enchantment

// display a ritual
// operator overload with a ritual

// help command

// display a hand

//

