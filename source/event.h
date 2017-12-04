#ifndef EVENT_H
#define EVENT_H

enum class Event {
    minionDied,
    minionDealtDamage,
    minionTookDamage,
    minionEnteredPlay,
    enemyMinionEnteredPlay,
    minionEnteredPlayControlled,
    endTurn,
    thisEndTurn,
    startTurn,
    thisStartTurn,
    cardDrawn,
    playerTookDamage,
    enchantmentPlaced,
    enchantmentRemoved,
    ritualPlaced,
    ritualRemoved,
    spellCast
};

#endif
