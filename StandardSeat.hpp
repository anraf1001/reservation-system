#pragma once

#include "Person.hpp"
#include "Seat.hpp"

constexpr char standardSeatSymbol = 'S';
constexpr unsigned int standardPrice = 370;

class StandardSeat : public Seat {
public:
    StandardSeat(unsigned int id, std::shared_ptr<Person> owner) noexcept
        : Seat(standardSeatSymbol, id, owner) {}
    StandardSeat(unsigned int id) noexcept
        : Seat(standardSeatSymbol, id) {}

    [[nodiscard]] constexpr unsigned int getPrice() const noexcept override { return standardPrice; }
};
