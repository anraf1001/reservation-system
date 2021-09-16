#include "Seat.hpp"

std::ostream& operator<<(std::ostream& out, const Seat& seat) {
    const char statusChar = seat.isTaken() ? ':' : '|';

    out << statusChar << seat.getSymbol() << statusChar;

    return out;
}
