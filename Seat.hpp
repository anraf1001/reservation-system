#pragma once

#include <memory>
#include <ostream>

#include "Person.hpp"

class Seat {
public:
    Seat(char symbol, unsigned int id, std::shared_ptr<Person> owner) noexcept
        : symbol_{symbol}, id_{id}, owner_{owner} {}
    Seat(char symbol, unsigned int id) noexcept
        : Seat{symbol, id, nullptr} {}
    virtual ~Seat() = default;

    char getSymbol() const noexcept { return symbol_; }
    unsigned int getID() const noexcept { return id_; }
    std::shared_ptr<Person> getOwner() const noexcept { return owner_; }
    bool isTaken() const noexcept { return owner_ != nullptr; }
    virtual constexpr unsigned int getPrice() const noexcept = 0;

    void take(std::shared_ptr<Person> newOwner) noexcept { owner_ = newOwner; }
    void free() noexcept { owner_.reset(); }

protected:
    const char symbol_;
    const unsigned int id_;
    std::shared_ptr<Person> owner_;
};

std::ostream& operator<<(std::ostream& out, const Seat& seat) {
    if (seat.isTaken()) {
        out << ':' << seat.getSymbol() << ':';
    } else {
        out << '[' << seat.getSymbol() << ']';
    }
    return out;
}
