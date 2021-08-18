#pragma once

#include "Seat.hpp"

constexpr char disabledSeatSymbol = 'D';
constexpr unsigned int disabledPrice = 250;

class DisabledSeat : public Seat {
public:
    DisabledSeat(unsigned int id, bool isTaken)
        : Seat(disabledSeatSymbol, id, disabledPrice, isTaken) {}
};
