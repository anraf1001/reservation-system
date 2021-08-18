#pragma once

class Seat {
public:
    Seat(char symbol, unsigned int id, unsigned int price, bool isTaken) noexcept
        : symbol_{symbol}, id_{id}, price_{price}, isTaken_{isTaken} {}

    char getSymbol() const noexcept { return symbol_; }
    unsigned int getID() const noexcept { return id_; }
    bool isTaken() const noexcept { return isTaken_; }
    unsigned int getPrice() const noexcept { return price_; }

    void take() noexcept { isTaken_ = true; }
    void free() noexcept { isTaken_ = false; }

protected:
    const char symbol_;
    const unsigned int id_;
    const unsigned int price_;
    bool isTaken_;
};
