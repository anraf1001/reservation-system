#pragma once

#include <memory>

#include "Person.hpp"

class Seat {
public:
    Seat(char symbol, unsigned int id, unsigned int price, std::shared_ptr<Person> owner) noexcept
        : symbol_{symbol}, id_{id}, price_{price}, owner_{owner} {}
    Seat(char symbol, unsigned int id, unsigned int price) noexcept
        : Seat{symbol, id, price, nullptr} {}

    char getSymbol() const noexcept { return symbol_; }
    unsigned int getID() const noexcept { return id_; }
    std::shared_ptr<Person> getOwner() const noexcept { return owner_; }
    bool isTaken() const noexcept { return owner_ != nullptr; }
    unsigned int getPrice() const noexcept { return price_; }

    void take(std::shared_ptr<Person> newOwner) noexcept { owner_ = newOwner; }
    void free() noexcept { owner_.reset(); }

protected:
    const char symbol_;
    const unsigned int id_;
    const unsigned int price_;
    std::shared_ptr<Person> owner_;
};
