#pragma once

#include <memory>
#include <vector>

#include "Seat.hpp"

using Row = std::vector<std::unique_ptr<Seat>>;
using Stadium = std::vector<Row>;

class ReservationSystem {
public:
    ReservationSystem();

private:
};
