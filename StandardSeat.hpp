#pragma once

#include "Seat.hpp"

class StandardSeat : public Seat {
public:
    StandardSeat(unsigned int id, bool isTaken) noexcept
        : Seat('S', id, isTaken) {}
};
