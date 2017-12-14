# Sorcery: an object-oriented implementation of Magic: The Gathering

![Screenshot of Empty Board](https://i.imgur.com/T68lzh3.png?1)

## Basic Game Rules and Logic

* Sorcery is a basic card game consisting of two players with decks consisting of minions, rituals, spells, and enchantments.
* The goal of the game is to bring the other player's health down by attacking him using the cards that you pull from you deck.
* Minions (the middle rows) can be played from your hand onto the field, where they can be used to attack other minions or the other player.
* Rituals (top-left and bottom-left) are special cards that have a special ability, inflicting an effect on the state of the game.
* The graveyard (top-right and bottom-right) holds the respective players' "dead" or used-up cards

![Screenshot of Filled Board](https://i.imgur.com/2Jp0MYc.png?1)

## Command-line Arguments

* `-deck1 deckList1.deck` and/or `-deck2 deckList2.deck` will take custom decks
* `-init tests.test` will read the file `tests.test` as stdin
* `-testing` flag will *not* shuffle the decks at the start of the game
* `-graphics` enables the X11 graphical interface alongside the TextDisplay

## Commands

* `help` -- Display this message.
* `end` -- End the current player's turn.
* `quit` -- End the game.
* `attack minion other-minion` -- Orders minion to attack other-minion.
* `attack minion` -- Orders minion to attack opponent.
* `play card [target-player target-card]` -- Play card, optionally targeting target-card owned by target-player.
* `use minion [target-player target-card]` -- Use minion's special ability, optionally targeting target-card owned by target-player.
* `inspect minion` -- View a minion's card and all enchantments on that minion.
* `hand` -- Describe all cards in your hand.
* `board` -- Describe all cards on the board.

## Design Patterns and Idioms

### Model-View-Controller

* To decrease coupling and increase cohesion, the game was implemented as three different components
* The view handled all displaying of information. Since the subject-observer pattern was used, the only thing the controller ever had to do was notify its observers.
* The model consisted of all the Cards (that is, minions, enchantments, players (!), etc.)
* The controller was the Board, which controlled the state of the game.

### Model-Controller within Objects

* Because certain cards were able to effectively change the state of the board (and therefore required access to the Board), the cards were given a static pointer to the Model of the Board. As a result, they were unable to access the implementation, but were still able to effect the state of the board.

### Subject-observer pattern

* To facilitate the addition of two different views, namely the GraphicsDisplay (which uses X11 libraries) and the TextDisplay (which simply outputs to stdout), the subject-observer pattern was used.
* Each view was a concrete observer of the Board, which would notify the views of any relevant commands