#pragma once

class Seat {
public:
    Seat(unsigned int id, bool isTaken) noexcept
        : id_{id}, isTaken_{isTaken} {}

    unsigned int getID() const noexcept { return id_; }
    bool isTaken() const noexcept { return isTaken_; }

    void take() noexcept { isTaken_ = true; }

protected:
    const unsigned int id_;
    bool isTaken_;
};
