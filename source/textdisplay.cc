#include "textdisplay.h"
#include "ascii_graphics.h"
#include "subject.h"
#include "player.h"
#include "info.h"
#include "minion.h"
#include "ritual.h"
#include "enchantment.h"
#include <iostream>

// constructor
TextDisplay::TextDisplay() {
  // initialize the theDisplay

  // start by creating an empty display with just templates
  std::cout << "textdisplay.cc: Initializing TextDisplay." << std::endl;

  std::vector<row_template_r> emptyRows;  
  // draw an empty enchantment
  for (int i = 0; i < 2; ++i) {
    // drawing empty rows for minions
    row_template_r emptyRow;
    for (int j = 0; j < cardsPerRow; ++j) {
      emptyRow.emplace_back(CARD_TEMPLATE_EMPTY);
    }
    emptyRows.emplace_back(emptyRow);
    enchantments.emplace_back(emptyRows);
  }

  minions = emptyRows;
  players = emptyRows;
  hands = emptyRows;
}

TextDisplay::~TextDisplay() {
  minions.clear();
  players.clear();
  hands.clear();
}

void TextDisplay::notifyDisplay(Subject &whoNotified, State command, int currentPlayer, int minionIndex) {
  std::cout << "textdisplay.cc: I have been notified by player "<< currentPlayer << "." << std::endl;
  // update the board when I'm notified
  this->currentPlayer = currentPlayer;
  this->minionIndex = minionIndex;

  std::cout << "textdisplay.cc: Updating myself with players information." << std::endl;
  std::vector<Info> boardInfos = whoNotified.getInfo();

  updatePlayers(boardInfos);
  updateHands(boardInfos);
  updateMinions(boardInfos);

  // let the display know what command was sent
  currentCommand = command;
}

// returns the correct card template for a given NonPlayer
card_template_t TextDisplay::cardTemplate(std::shared_ptr<NonPlayer> card) {

  std::string name = card->getName();
  int cost = card->getCost();
  std::string description = card->getDescription();

  // check if its a minion
  if (card->getType() == Type::Minion) {
    // dynamically cast this as a minion pointer
    std::shared_ptr<Minion> m = std::dynamic_pointer_cast<Minion>(card);    
    // get attack and defense
    int attack = m->getAttack();
    int defence = m->getDefence();
    std::cout << "attack: " << attack << " defense: " << defence << std::endl;
    
    // check if theres an ability
    if (m->hasAbility()) {
      std::cout << "I have been asked if I have an ability" << std::endl;
      // check the type of ability
      if (m->getAbilityType(0) == Type::ActivatedAbility) {
        // check the cost of the activated ability
        int abilityCost = m->getAbilityCost();
        return (display_minion_activated_ability(name, cost, attack, defence, abilityCost, description));
      } else {
        return (display_minion_triggered_ability(name, cost, attack, defence, description));
      }
    } else {
      return (display_minion_no_ability(name, cost, attack, defence));
    }
  }

  // check if its a ritual
  else if (card->getType() == Type::Ritual) {
    std::shared_ptr<Ritual> r = std::dynamic_pointer_cast<Ritual>(card);
    return (display_ritual(name, cost, r->getCost(), r->getDescription(), r->getCharges()));
  }

  // check if its a spell
  else if (card->getType() == Type::Spell) {
    return (display_spell(name, cost, description));
  }

  // check if its an enchantment
  else if (card->getType() == Type::Enchantment) {
    std::shared_ptr<Enchantment> e = std::dynamic_pointer_cast<Enchantment>(card);

    // UNCOMMENT THIS WHEN ENCHANTMENTS ARE IMPLEMENTED
    
    Type enchantmentType = e->getType();
    /*
    std::string attack = e->getAttackOperator() + e->getAttackModifier();
    std::string defence = e->getDefenceOperator() + e->getDefenceModifier();
    hands[i][j] = display_enchantment_attack_defence(name, cost, description, attack, defence));
    */
  }

  // if its not any of the known card types, print a basic card
  return display_spell(name, cost, description);
}

// updates players information
void TextDisplay::updatePlayers(std::vector<Info> boardInfos) {
  
  for (unsigned int i = 0; i < boardInfos.size(); ++i) {
    // the first card is the ritual
    // check if player one has a ritual
    if (boardInfos[i].ritual == nullptr) {
      players[i][0] = CARD_TEMPLATE_BORDER;
    } else {
      std::shared_ptr<Ritual> r = std::dynamic_pointer_cast<Ritual>(boardInfos[i].ritual);
      players[i][0] = (display_ritual(r->getName(), r->getCost(), r->getCost(), r->getDescription(), r->getCharges()));
    }
    
    // note that the second and fourth cards of the player row are always empty
    // this is due to the graphics described in project requirements

    // the third card is the player card
    players[i][2] = display_player_card(1, boardInfos[i].name, boardInfos[i].health, boardInfos[i].magic);

    // the last card is the top of the graveyard
    // this code is not yet implemented so for now we have an empty card
    if (boardInfos[i].graveyard == nullptr) {
      players[i][4] = CARD_TEMPLATE_BORDER;    
    } else {
      players[i][4] = cardTemplate(boardInfos[i].graveyard);
    }
  }
}

// update the players hands
void TextDisplay::updateHands(std::vector<Info> boardInfos) {

  for (unsigned int i = 0; i < boardInfos.size(); ++i) {  

    // we're going to empty our hand
    hands[i].clear();

    // update the hands of the players
    for (unsigned int j = 0; j < boardInfos[i].hand.size(); j++) { 
      hands[i].emplace_back(cardTemplate(boardInfos[i].hand[j]));
    }
  }
}

// update the players minions
void TextDisplay::updateMinions(std::vector<Info> boardInfos) {
  for (unsigned int i = 0; i < boardInfos.size(); ++i) {
    // we're going to fill our minion spots with an empty template
    for (int j = 0; j < 5; ++j) {
      minions[i][j] = CARD_TEMPLATE_BORDER;
      enchantments[i].clear(); // clear the enchantments
    }

    // if neither players have any minions, we're done
    if (boardInfos[i].minions.empty()) {
      continue;
    }

    // if we have minions, let's populate our field
    for (unsigned int j = 0; j < boardInfos[i].minions.size(); ++j) {
      minions[i][j] = cardTemplate(boardInfos[i].minions[j]);
      
      std::vector<card_template_t> enchantments;
      // add any enchantments for this minion
      for (auto enchantment : boardInfos[i].minions[j]->enchantments) {
        enchantments.emplace_back(cardTemplate(enchantment));
      }

      this->enchantments[i].emplace_back(enchantments);
    }

  }
}

// prints the board
void TextDisplay::printBoard(std::ostream &out) const {
  int playerIndex = 0;
  int cardWidth = 33; // change this later maybe

  // draw the top left border
  out << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  unsigned int width = cardWidth * players[currentPlayer].size();
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

  // draw player1's player row and minion row
  printRow(players[playerIndex], out, true);
  printRow(minions[playerIndex], out, true);  

  // print out the logo
  for (unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) {
    out << CENTRE_GRAPHIC[i] << std::endl;
  }

  // increment to the next player
  playerIndex++;

  printRow(minions[playerIndex], out, true);    
  printRow(players[playerIndex], out, true);

  // draw the bottom left border
  out << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;

}

// prints a given row of cardss
void TextDisplay::printRow(row_template_r row, std::ostream &out, bool border) const {
  // print out the hand by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    
    if (border) {
      // draw the left-hand side vertical border
      out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    }
    // go through each card
    for (unsigned int j = 0; j < row.size(); ++j) {
      // print the i'th line of each of the cards in the hand
      out << row[j][i];
    }
    if (border) {
      // draw the right-hand side vertical border
      out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    }
    out << std::endl;
  }
}

// inspects a minion
void TextDisplay::inspectMinion(std::ostream &out) const {
  // we need to get the name, cost, description, attack, defence
  // if it has an ability, we need the name and cost of that too
  // we need to check if a minion has an enchantment on it
  // we need to figure out what kind of enchantment it is
  // we need the name, cost, description of it
  
  // print our minion
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    out << minions[currentPlayer][minionIndex][i] << std::endl;
  }

  row_template_r enchantmentRow;
  for (auto enchantment : enchantments[currentPlayer][minionIndex]) {
    // print out each row of enchantments
    for (unsigned int i = 0; i < cardsPerRow; ++i) {
      enchantmentRow.emplace_back(enchantment);
    }
    printRow(enchantmentRow, out);
    enchantmentRow.clear();
  }
}

void TextDisplay::printHand(std::ostream &out) const {
  printRow(hands[currentPlayer], out);
}

void TextDisplay::printHelp(std::ostream &out) const {
  out <<
	"help -- Display this message." << std::endl <<
	"end -- End the current player's turn." << std::endl <<
	"quit -- End the game." << std::endl <<
	"attack minion other-minion -- Orders minion to attack other-minion." << std::endl <<
	"attack minion -- Orders minion to attack opponent." << std::endl <<
	"play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << std::endl <<
	"use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << std::endl <<
	"inspect minion -- View a minion's card and all enchantments on that minion." << std::endl <<
	"hand -- Describe all cards in your hand." << std::endl <<
	"board -- Describe all cards on the board." << std::endl;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {

  if (td.currentCommand == State::printBoard) {
    td.printBoard(out);
  } else if (td.currentCommand == State::printMinion) {
    td.inspectMinion(out);
  } else if (td.currentCommand == State::printHand) {
    td.printHand(out);
  } else if (td.currentCommand == State::printHelp) {
    td.printHelp(out);
  }
 
  return out;
}

