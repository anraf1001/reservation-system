#pragma once

#include "Seat.hpp"

constexpr char disabledSeatSymbol = 'D';

class DisabledSeat : public Seat {
public:
    DisabledSeat(unsigned int id, bool isTaken)
        : Seat(disabledSeatSymbol, id, isTaken) {}
};
