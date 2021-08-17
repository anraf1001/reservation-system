#pragma once

#include "Seat.hpp"

constexpr char standardSeatSymbol = 'S';

class StandardSeat : public Seat {
public:
    StandardSeat(unsigned int id, bool isTaken) noexcept
        : Seat(standardSeatSymbol, id, isTaken) {}
};
