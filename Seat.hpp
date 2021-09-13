#pragma once

#include <memory>
#include <ostream>

#include "Person.hpp"

class Seat {
public:
    Seat(char symbol, unsigned int id, const std::shared_ptr<Person>& owner) noexcept
        : symbol_{symbol}, id_{id}, owner_{owner} {}
    Seat(char symbol, unsigned int id) noexcept
        : Seat{symbol, id, nullptr} {}
    virtual ~Seat() = default;

    [[nodiscard]] virtual constexpr unsigned int getPrice() const noexcept = 0;

    [[nodiscard]] char getSymbol() const noexcept { return symbol_; }
    [[nodiscard]] unsigned getID() const noexcept { return id_; }
    [[nodiscard]] std::shared_ptr<Person> getOwner() const { return owner_; }
    [[nodiscard]] bool isTaken() const noexcept { return owner_ != nullptr; }

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
