#pragma once

#include "Seat.hpp"

constexpr char DisabledSeatSymbol = 'D';

class DisabledSeat : public Seat {
public:
    DisabledSeat(unsigned int id, bool isTaken)
        : Seat(DisabledSeatSymbol, id, isTaken) {}
};
