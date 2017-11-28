#include "textdisplay.h"
#include "ascii_graphics.h"
#include <iostream>

// constructor
TextDisplay::TextDisplay() {
  // initialize the theDisplay
  int cardsPerRow = 5;
  // start by creating an empty display with just templates

  // drawing an empty hand and field for player 1
  for (int i = 0; i < cardsPerRow; ++i) {
    playerOneField.emplace_back(CARD_TEMPLATE_BORDER);
    playerOneHand.emplace_back(CARD_TEMPLATE_BORDER);
  }

  for (int i = 0; i < cardsPerRow; ++i) {
    playerTwoField.emplace_back(CARD_TEMPLATE_BORDER);
    playerTwoHand.emplace_back(CARD_TEMPLATE_BORDER);
  }
  
  std::vector<card_template_t> logo = {CENTRE_GRAPHIC};
  
  //theDisplay.emplace_back(playerOneHand);
  //theDisplay.emplace_back(playerOneField);
  theDisplay.emplace_back(logo);
  //theDisplay.emplace_back(playerTwoField);
  //theDisplay.emplace_back(playerTwoHand);
}

TextDisplay::~TextDisplay() {

}

void TextDisplay::notifyDisplay(Subject &whoNotified) {
  // what to do when I'm notified
  // im thinking that a subject might give me info (as to what has been requested)

}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  int cardWidth = 33; // change this later maybe

  // draw the top left border
  out << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  unsigned int width = cardWidth * td.playerOneHand.size();
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;


  // print out the hand by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < td.playerOneHand.size(); ++j) {
      // print the i'th line of each of the cards in the hand
      out << td.playerOneHand[j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }

  // print out the field by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < td.playerOneField.size(); ++j) {
      out << td.playerOneField[j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }

  // print out the logo
  for (unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) {
    out << CENTRE_GRAPHIC[i] << std::endl;
  }

  // print out the field by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < td.playerTwoField.size(); ++j) {
      out << td.playerTwoField[j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }

  // print out the hand by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < td.playerTwoHand.size(); ++j) {
      // print the i'th line of each of the cards in the hand
      out << td.playerTwoHand[j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }

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

