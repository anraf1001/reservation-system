#pragma once

#include "Seat.hpp"

constexpr char vipSeatSymbol = 'V';
constexpr unsigned int vipPrice = 1000;

class VIPSeat : public Seat {
public:
    VIPSeat(unsigned int id, bool isTaken)
        : Seat(vipSeatSymbol, id, vipPrice, isTaken) {}
};
