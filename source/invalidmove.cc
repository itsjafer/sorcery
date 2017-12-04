#include "invalidmove.h"

using namespace std;

InvalidMoveException::InvalidMoveException(InvalidMove im) {
    switch(im) {
        case InvalidMove::BadPlay:
            message = "Cannot play that card!";
            break;
        case InvalidMove::FieldFull:
            message = "Your field is already full!";
            break;
        case InvalidMove::InsufficientMagic:
            message = "You do not have enough magic to do this!";
            break;
        case InvalidMove::NoActivatedAbility:
            message = "That minion does not have an activated ability!";
            break;
        case InvalidMove::CannotUseMinion:
            message = "You cannot currently use this minion!";
    }
}

const string &InvalidMoveException::what() const {
    return message;
}
