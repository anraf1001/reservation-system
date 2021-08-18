#pragma once

#include "Seat.hpp"

constexpr char vipSeatSymbol = 'V';

class VIPSeat : public Seat {
public:
    VIPSeat(unsigned int id, bool isTaken)
        : Seat(vipSeatSymbol, id, isTaken) {}
};
