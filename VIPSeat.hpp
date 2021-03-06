#pragma once

#include "Seat.hpp"

constexpr char vipSeatSymbol = 'V';
constexpr unsigned int vipPrice = 1000;

class VIPSeat : public Seat {
public:
    VIPSeat(unsigned int id, const std::shared_ptr<Person>& owner) noexcept
        : Seat(vipSeatSymbol, id, owner) {}
    VIPSeat(unsigned int id) noexcept
        : Seat(vipSeatSymbol, id) {}

    [[nodiscard]] constexpr unsigned int getPrice() const noexcept override { return vipPrice; }
};
