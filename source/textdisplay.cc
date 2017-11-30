#include "textdisplay.h"
#include "ascii_graphics.h"
#include "subject.h"
#include "player.h"
#include "nonplayer.h"
#include "info.h"
#include "minion.h"
#include "enchantment.h"
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
    minionRow.emplace_back(temp);
    playerRow.emplace_back(temp);
  }
}

TextDisplay::~TextDisplay() {

}

void TextDisplay::notifyDisplay(Subject &whoNotified, State command, int minion) {
  std::cout << "textdisplay.cc: I have been notified." << std::endl;
  // update the board when I'm notified
  std::cout << "textdisplay.cc: Updating myself with players information." << std::endl;
  update(whoNotified);

  // let the display know what command was sent
  currentCommand = command;
}

// updates all information about a board based on who we were notified by
void TextDisplay::update (Subject &whoNotified) {
  std::cout << "textdisplay.cc: I'm going to print now." << std::endl;
  std::vector<Info> boardInfos = whoNotified.getInfo();

  // loop through each player
  for (unsigned int i = 0; i < boardInfos.size(); ++i) {
    
    // update the player row

    // the first card is the ritual
    // check if player one has a ritual
    // this code is not yet implemented so for now we have an empty card
    if (boardInfos[i].ritual == nullptr) {
      playerRow[i][0] = CARD_TEMPLATE_BORDER;
    }
    
    // note that the second and fourth cards of the player row are always empty
    // this is due to the graphics described in project requirements

    // the third card is the player card
    playerRow[i][2] = display_player_card(1, boardInfos[i].name, boardInfos[i].health, boardInfos[i].magic);

    // the last card is the top of the graveyard
    // this code is not yet implemented so for now we have an empty card
    if (boardInfos[i].graveyard == nullptr) {
      playerRow[i][4] = CARD_TEMPLATE_BORDER;    
    }

    // update the hands of the players
    for (unsigned int j = 0; j < boardInfos[i].hand.size(); j++) {
      // get the name of the card
      std::string name = boardInfos[i].hand[j]->getName();

      // get the cost of the card
      int cost = boardInfos[i].hand[j]->getCost();

      // get the description of the card
      std::string description = boardInfos[i].hand[j]->getDescription();

      // check if its a minion
      if (boardInfos[i].hand[j]->getType() == Type::Minion) {
        // dynamically cast this as a minion pointer
        std::shared_ptr<Minion> m = std::dynamic_pointer_cast<Minion>(boardInfos[i].hand[j]);
        
        // get attack and defense
        //int attack = m->getAttack();
        //int defence = m->getDefence();
        
        // UNCOMMENT THIS WHEN ABILITIES ARE IMPLEMENTED
        /*
        // check if theres an ability
        if (m->hasAbility()) {

          // check the type of ability
          if (m->getAbilityType(0) == Type::ActivatedAbility) {
            // check the cost of the activated ability
            int abilityCost = m->getAbilityCost();
            hands[i][j] + (display_minion_activated_ability(name, cost, attack, defence, abilityCost, description));
          } else {
            hands[i][j] = (display_minion_triggered_ability(name, cost, attack, defence, description));
          }
        } else {
          hands[i][j] = (display_minion_no_ability(name, cost, attack, defence));
        }*/

      }

      // check if its a ritual
      else if (boardInfos[i].hand[j]->getType() == Type::Ritual) {
        //std::shared_ptr<Ritual> r = std::dynamic_pointer_cast<Ritual>(boardInfos[i].hand[j]);
        // UNCOMMENT THIS WHEN RITUALS ARE IMPLEMENTED
        // hands[i][j] = (display_ritual(name, cost, r->getCost(), r->getDescription(), r->getCharges()));

      }

      // check if its a spell
      else if (boardInfos[i].hand[j]->getType() == Type::Spell) {
        hands[i][j] = (display_spell(name, cost, description));
      }

      // check if its an enchantment
      else if (boardInfos[i].hand[j]->getType() == Type::Enchantment) {
        //std::shared_ptr<Enchantment> e = std::dynamic_pointer_cast<Enchantment>(boardInfos[i].hand[j]);

        // UNCOMMENT THIS WHEN ENCHANTMENTS ARE IMPLEMENTED
        /*
        Type enchantmentType = e->getType();

        std::string attack = e->getAttackOperator() + e->getAttackModifier();
        std::string defence = e->getDefenceOperator() + e->getDefenceModifier();
        hands[i][j] = display_enchantment_attack_defence(name, cost, description, attack, defence));
        */
      }

    }
    // update the minion row

    // we're going to fill our minion spots with an empty template
    for (int j = 0; j < 5; ++j) {
      minionRow[i][j] = CARD_TEMPLATE_BORDER;
    }

    // if neither players have any minions, we're done
    if (boardInfos[i].minions.empty() || boardInfos[i].minions.empty()) {
      continue;
    }

    // if we have minions, let's populate our field
    for (unsigned int j = 0; j < boardInfos[i].minions.size(); ++j) {
      // print out the minions here.
      // need to figure out a way to determine activated vs triggered
    }
  }
}

void TextDisplay::printHand(std::ostream &out) const {

}

void TextDisplay::printBoard(std::ostream &out) const {
  int currentPlayer = 0;
  int cardWidth = 33; // change this later maybe

  // draw the top left border
  out << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  unsigned int width = cardWidth * playerRow[currentPlayer].size();
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

  printPlayerRow(currentPlayer, out);
  printMinionRow(currentPlayer, out);
  

  // print out the logo
  for (unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) {
    out << CENTRE_GRAPHIC[i] << std::endl;
  }

  // increment to the next player
  currentPlayer++;

  printMinionRow(currentPlayer, out);
  printPlayerRow(currentPlayer, out);

  // draw the bottom left border
  out << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (unsigned int j = 0; j < width; ++j) {
    // drawing the horizontal top border
    out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  // draw the horizontal top right border
  out << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;

}

void TextDisplay::printPlayerRow(int currentPlayer, std::ostream &out) const {
  // print out the hand by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < playerRow[currentPlayer].size(); ++j) {
      // print the i'th line of each of the cards in the hand
      out << playerRow[currentPlayer][j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }
}

void TextDisplay::printMinionRow(int currentPlayer, std::ostream &out) const {
  // print out the field by printing from top to bottom of each card
  for (unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); ++i) {
    // draw the left-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    // go through each card
    for (unsigned int j = 0; j < minionRow[currentPlayer].size(); ++j) {
      out << minionRow[currentPlayer][j][i];
    }
    // draw the right-hand side vertical border
    out << EXTERNAL_BORDER_CHAR_UP_DOWN;
    out << std::endl;
  }
}

void TextDisplay::printMinion(std::ostream &out) const {
  // we need to get the name, cost, description, attack, defence
  // if it has an ability, we need the name and cost of that too
  // we need to check if a minion has an enchantment on it
  // we need to figure out what kind of enchantment it is
  // we need the name, cost, description of it

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
    td.printMinion(out);
  } else if (td.currentCommand == State::printHand) {
    //td.printHand(out);
  } else if (td.currentCommand == State::printHelp) {
    td.printHelp(out);
  }
 
  return out;
}

