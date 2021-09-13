#include "Seat.hpp"

std::ostream& operator<<(std::ostream& out, const Seat& seat) {
    if (seat.isTaken()) {
        out << ':' << seat.getSymbol() << ':';
    } else {
        out << '[' << seat.getSymbol() << ']';
    }
    return out;
}
