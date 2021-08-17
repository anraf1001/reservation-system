#pragma once

class Seat {
public:
    Seat(char symbol, unsigned int id, bool isTaken) noexcept
        : symbol_{symbol}, id_{id}, isTaken_{isTaken} {}
    ~Seat() = default;

    char getSymbol() const noexcept { return symbol_; }
    unsigned int getID() const noexcept { return id_; }
    bool isTaken() const noexcept { return isTaken_; }

    void take() noexcept { isTaken_ = true; }

protected:
    const char symbol_;
    const unsigned int id_;
    bool isTaken_;
};
