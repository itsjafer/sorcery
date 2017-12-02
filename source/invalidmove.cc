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
    }
}

const string &InvalidMoveException::what() const {
    return message;
}
