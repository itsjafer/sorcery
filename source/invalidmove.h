#ifndef INVALID_MOVE
#define INVALID_MOVE

#include <string>

enum class InvalidMove {
    BadPlay,
    FieldFull,
    InsufficientMagic,
    NoActivatedAbility,
    CannotUseMinion,
    NoChargesLeft,
    InsufficientMagicRitual
};

class InvalidMoveException {
    std::string message;
public:
    InvalidMoveException(InvalidMove im);
    const std::string &what() const;
};

#endif
