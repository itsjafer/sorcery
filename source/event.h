#ifndef EVENT_H
#define EVENT_H

enum class Event {
    minionDied,
    minionDealtDamage,
    minionTookDamage,
    minionEnteredPlay,
    endTurn,
    startTurn,
    cardDrawn,
    playerTookDamage,
    enchantmentPlaced,
    enchantmentRemoved,
    ritualPlaced,
    ritualRemoved,
    spellCast
};

#endif
