#pragma once

#include <memory>

#include "Person.hpp"
#include "Seat.hpp"

template <typename T>
concept DerivedFromSeat = std::derived_from<T, Seat>;

class SeatPtrFactory {
public:
    SeatPtrFactory() = default;

    template <DerivedFromSeat T>
    std::unique_ptr<Seat> createSeatPtr(const std::shared_ptr<Person>& owner) {
        return std::make_unique<T>(++actualID, owner);
    }

private:
    unsigned actualID{};
};
