#include "graphicsdisplay.h"
#include "boardcontroller.h"
#include "playermodel.h"
#include "minion.h"
#include "ritual.h"
#include "enchantment.h"
#include "ability.h"
#include "nonplayer.h"
#include <iostream>

// constructor
GraphicsDisplay::GraphicsDisplay(int winSize) : winSize(winSize), xw(winSize * 2, winSize) {
  // initialize the graphicsDisplay

  // set the card sizes
  cardWidth = (winSize * 2 ) / 5;
  logoHeight = winSize / 5;
  cardHeight = (winSize - logoHeight) / 5;
  spacing = cardHeight / 8;
  // start by creating an empty display with just templates
  std::cout << "graphicsdisplay.cc: Initializing graphicsdisplay." << std::endl;
  xw.fillRectangle(0, 0, winSize * 2, winSize, Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() {
 
}

void GraphicsDisplay::notifyDisplay(BoardController &whoNotified, State command, int minionIndex) {
  xw.fillRectangle(0, 0, winSize * 2, winSize, Xwindow::Black);  
  currentPlayer = whoNotified.getCurrentPlayer();
  std::cout << "graphicsdisplay.cc: I have been notified by player " << currentPlayer << "." << std::endl;

  // update the board when I'm notified
  this->minionIndex = minionIndex;

  std::cout << "graphicsdisplay.cc: Updating myself with players information." << std::endl;
  std::vector<PlayerModel> boardInfos = whoNotified.getPlayerInfos();

  displayPlayers(boardInfos);
  displayMinions(boardInfos);
  displayHand(boardInfos);

  // display the logo
  xw.drawBigString(0, cardHeight * (3 - currentPlayer) + cardHeight / (3 - currentPlayer), "SORCERY", Xwindow::White);
  
  if (command == State::printMinion) {
    xw.fillRectangle(0, 0, winSize * 2, winSize, Xwindow::Black);    
    inspectMinion(boardInfos);
  } else if (command == State::printHand) {
    xw.fillRectangle(0, 0, winSize * 2, winSize, Xwindow::Black);    
    displayHand(boardInfos);
  } else if (command == State::printHelp) {
    displayHelp();
  }

}

void GraphicsDisplay::displayHelp() {
  int height = winSize * 0.5;
  int width = winSize;
  int x = width / 2;
  int y = height / 2 + spacing;
  xw.fillRectangle(x, y, width, height, Xwindow::Cyan);
  y += spacing;
  
  std::vector<std::string> helpMessages = {
	"help -- Display this message." ,
	"end -- End the current player's turn.",
	"quit -- End the game.",
	"attack minion other-minion -- Orders minion to attack other-minion.",
	"attack minion -- Orders minion to attack opponent.",
	"play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.",
	"use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.",
	"inspect minion -- View a minion's card and all enchantments on that minion.",
	"hand -- Describe all cards in your hand.",
	"board -- Describe all cards on the board."
  };

  for (auto message : helpMessages) {
    xw.drawString(x, y, message);
    y += spacing * 2;
  }

}

void GraphicsDisplay::displayHand(std::vector<PlayerModel> boardInfos) {
  int height = 0;
  int width = 0;
  if (currentPlayer == 1) {
    height = winSize - cardHeight;
  }
  for (int i = 0; i < boardInfos[currentPlayer].hand.size(); i++) {
    displayCard(boardInfos[currentPlayer].hand[i], width, height);
    width += cardWidth;
  }
} 

void GraphicsDisplay::inspectMinion(std::vector<PlayerModel> boardInfos) {
  xw.fillRectangle(0, 0, winSize * 2, winSize, Xwindow::Black);  
  int heightIndex = 0;
  int widthIndex = 0;

  displayCard(boardInfos[currentPlayer].minions[minionIndex], 0, heightIndex);
  heightIndex += cardHeight;

  if (boardInfos[currentPlayer].minions[minionIndex]->enchantments.empty()) {
    return;
  }

  for (int i = 0; i > boardInfos[currentPlayer].minions[minionIndex]->enchantments.size(); ++i) {
    if (widthIndex >= winSize * 2) {
      widthIndex = 0;
      heightIndex += cardHeight;
    }
    displayCard(boardInfos[currentPlayer].minions[minionIndex]->enchantments[i], widthIndex, heightIndex);
    widthIndex += cardWidth;
  }
}

void GraphicsDisplay::displayDescription(std::string description, int x, int y) {
  int width = cardWidth / 6; // each character is 6 pixels wide
  int numRows = description.length() / (width);
  std::vector<std::string> rows;

  for (auto i = 0; i < numRows; i++)
  {
      rows.emplace_back(description.substr(i * width, width));
  }

  if (description.length() % width != 0)
  {
      rows.emplace_back(description.substr(width * numRows));
  }
  
  for (auto row : rows) {
    xw.drawString(x, y, row);
    y += spacing;    
  }
}

void GraphicsDisplay::displayCard(std::shared_ptr<NonPlayer> card, int x, int y) {
  std::string name = card->getName();
  int cost = card->getCost();
  std::string description = card->getDescription();

  if (card->getType() == Type::Minion) {
    // dynamically cast this as a minion pointer
    std::shared_ptr<Minion> m = std::dynamic_pointer_cast<Minion>(card);    
    // get attack and defense
    int attack = m->getAttack();
    int defence = m->getDefence();
    
    // check if theres an ability
    if (m->hasAbility()) {
      // get the description of the abilities
      description = "";
      for (auto ability : m->abilities) {
        description = ability->getDescription();
      }
      
      // check the type of ability
      if (m->getAbilityType(0) == Type::ActivatedAbility) {
        // check the cost of the activated ability
        int abilityCost = m->getAbilityCost();
        xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Blue);
        int totalSpacing = y + spacing;
        xw.drawString(x, totalSpacing, name);
        totalSpacing += spacing;
        xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
        totalSpacing += spacing;
        xw.drawString(x, totalSpacing, "Minion");
        totalSpacing += spacing;
        xw.drawString(x, totalSpacing, "Ability Cost: " + std::to_string(abilityCost));
        totalSpacing += spacing;
        displayDescription(description, x, totalSpacing);

        y += cardHeight - spacing;
        xw.drawString(x, y, "Attack: " + std::to_string(attack));
        y += spacing;
        xw.drawString(x, y, "Defence: " + std::to_string(defence));
      } else {
        xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Blue);
        int totalSpacing = y + spacing;
        xw.drawString(x, totalSpacing, name);
        totalSpacing += spacing;
        xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
        totalSpacing += spacing;
        xw.drawString(x, totalSpacing, "Minion");
        totalSpacing += spacing;
        displayDescription(description, x, totalSpacing);

        y += cardHeight - spacing;
        xw.drawString(x, y, "Attack: " + std::to_string(attack));
        y += spacing;
        xw.drawString(x, y, "Defence: " + std::to_string(defence));   
      }
    } else {
      xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Blue);
      int totalSpacing = y + spacing;
      xw.drawString(x, totalSpacing, name);
      totalSpacing += spacing;
      xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
      totalSpacing += spacing;
      xw.drawString(x, totalSpacing, "Minion");

      y += cardHeight - spacing;
      xw.drawString(x, y, "Attack: " + std::to_string(attack));
      y += spacing;
      xw.drawString(x, y, "Defence: " + std::to_string(defence));     
    }
  }
   else if (card->getType() == Type::Ritual) {
    std::shared_ptr<Ritual> r = std::dynamic_pointer_cast<Ritual>(card);
    xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Brown);
    int totalSpacing = y + spacing;    
    xw.drawString(x, totalSpacing, name);
    totalSpacing += spacing;
    xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
    totalSpacing += spacing;
    xw.drawString(x, totalSpacing, "Ritual");
    totalSpacing += spacing;
    displayDescription(r->getDescription(), x, totalSpacing);    
    y += cardHeight - spacing;
    xw.drawString(x, y, "Charges: " + std::to_string(r->getCharges()));
  }

  // check if its a spell
  else if (card->getType() == Type::Spell) {
    xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Red);
    int totalSpacing = y + spacing;
    xw.drawString(x, totalSpacing, name);
    totalSpacing += spacing;
    xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
    totalSpacing += spacing;
    xw.drawString(x, totalSpacing, "Spell");
    totalSpacing += spacing;
    displayDescription(description, x, totalSpacing);     
  }

  else if (card->getType() == Type::AddEnchantment) {
    std::shared_ptr<AddEnchant> e = std::dynamic_pointer_cast<AddEnchant>(card);

    if (e->getAttackModifier() == 0 && e->getDefenceModifier() == 0) {
      //return display_enchantment(name, cost, description);
      xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Green);   
      int totalSpacing = y + spacing;
      xw.drawString(x, totalSpacing, name);
      totalSpacing += spacing;
      xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
      totalSpacing += spacing;
      xw.drawString(x, totalSpacing, "Enchantment");
      totalSpacing += spacing;
      displayDescription(description, x, totalSpacing);            
    }

    std::string attack = e->getAttackOperator() + std::to_string(e->getAttackModifier());
    std::string defence = e->getDefenceOperator() + std::to_string(e->getDefenceModifier());

    xw.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::Green);     
    int totalSpacing = y + spacing;
    xw.drawString(x, totalSpacing, name);
    totalSpacing += spacing;
    xw.drawString(x, totalSpacing, "Cost: " + std::to_string(cost));
    totalSpacing += spacing;
    xw.drawString(x, totalSpacing, "Enchantment");
    totalSpacing += spacing;
    displayDescription(description, x, totalSpacing);

    y += cardHeight - spacing;
    xw.drawString(x, y, "Attack: " + attack);
    y += spacing;
    xw.drawString(x, y, "Defence: " + defence);   
  }          
  
}

void GraphicsDisplay::displayPlayers(std::vector<PlayerModel> boardInfos) {

  int heightIndex = 0;
  if (currentPlayer == 0) {
    heightIndex = cardHeight; // account for the hand displayed above
  }
  for (int i = 0; i < boardInfos.size(); ++i) {
    // draw the ritual
    if (boardInfos[i].ritual != nullptr) {
      displayCard(boardInfos[i].ritual, 0, 0);
    } else {
      xw.fillRectangle(0, heightIndex, cardWidth, cardHeight, Xwindow::White); 
    }

    // draw the player card
    int widthIndex = cardWidth * 2;
    xw.fillRectangle(widthIndex, heightIndex, cardWidth, cardHeight, Xwindow::White);
    int tempIndex = heightIndex;

    heightIndex += spacing; // magic number to account for font size
    xw.drawString(widthIndex + spacing, heightIndex, boardInfos[i].name, Xwindow::Black);
    heightIndex += spacing;
    xw.drawString(widthIndex, heightIndex, "Health: " + std::to_string(boardInfos[i].health));
    heightIndex += spacing;
    xw.drawString(widthIndex, heightIndex, "Magic: " + std::to_string(boardInfos[i].magic));
    heightIndex = tempIndex;

    // draw the graveyard
    if (!boardInfos[i].graveyard.empty()) {
      displayCard(boardInfos[i].graveyard.back(), cardWidth * 4, 0);
    } else {
      xw.fillRectangle(cardWidth * 4, heightIndex, cardWidth, cardHeight, Xwindow::White); 
    }

    // update the heightIndex to print player 2's row
    if (currentPlayer == 0) {      
      heightIndex = winSize - cardHeight;
    } else {
      heightIndex = winSize - (cardHeight * 2);
    }
  }
}

void GraphicsDisplay::displayMinions(std::vector<PlayerModel> boardInfos) {
  int heightIndex = cardHeight;
  if (currentPlayer == 0) {
    heightIndex += cardHeight; // account for the hand displayed above
  }
  for (int i = 0 ; i < boardInfos.size(); ++i) {
    for (int j = 0; j < winSize * 2; j+= cardWidth) {
      // fill minion slots with white space
      xw.fillRectangle(j, heightIndex, cardWidth, cardHeight, Xwindow::White); 
    }

    //skip if there's no minions
    if (boardInfos[i].minions.empty()) {
      heightIndex = winSize - (2 * cardHeight);
      continue;
    }


    int widthIndex = 0;
    for (unsigned int j = 0; j < boardInfos[i].minions.size(); ++j) {
      displayCard(boardInfos[i].minions[j], widthIndex, heightIndex);
      widthIndex += cardWidth;
    }

    if (currentPlayer == 0) {      
      heightIndex = winSize - (2 * cardHeight);
    } else {
      heightIndex = winSize - (cardHeight * 3);
    }
  }
}