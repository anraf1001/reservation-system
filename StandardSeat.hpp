#pragma once

#include "Seat.hpp"

constexpr char standardSeatSymbol = 'S';
constexpr unsigned int standardPrice = 370;

class StandardSeat : public Seat {
public:
    StandardSeat(unsigned int id, bool isTaken) noexcept
        : Seat(standardSeatSymbol, id, standardPrice, isTaken) {}
};
