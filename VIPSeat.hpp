#pragma once

#include "Seat.hpp"

constexpr char VIPSeatSymbol = 'V';

class VIPSeat : public Seat {
public:
    VIPSeat(unsigned int id, bool isTaken)
        : Seat(VIPSeatSymbol, id, isTaken) {}
};
