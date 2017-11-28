#include "textdisplay.h"

// constructor
TextDisplay::TextDisplay() {
  // initialize the theDisplay
  // its unclear right now what its default value is
}

void TextDisplay::notifyDisplay(Subject &whoNotified) {
  // what to do when I'm notified
  // im thinking that a subject might give me an event

}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  // out the current display
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

