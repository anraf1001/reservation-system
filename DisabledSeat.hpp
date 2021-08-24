#pragma once

#include "Seat.hpp"

constexpr char disabledSeatSymbol = 'D';
constexpr unsigned int disabledPrice = 250;

class DisabledSeat : public Seat {
public:
    DisabledSeat(unsigned int id, std::shared_ptr<Person> owner) noexcept
        : Seat(disabledSeatSymbol, id, disabledPrice, owner) {}
    DisabledSeat(unsigned int id) noexcept
        : Seat(disabledSeatSymbol, id, disabledPrice) {}
};
