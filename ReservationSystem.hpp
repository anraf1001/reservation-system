#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include "Person.hpp"
#include "Seat.hpp"

namespace fs = std::filesystem;

using Persons = std::vector<std::shared_ptr<Person>>;
using Row = std::vector<std::unique_ptr<Seat>>;
using Stadium = std::vector<Row>;

class ReservationSystem {
public:
    ReservationSystem();

private:
    void readClientsDatabase(const fs::path& database);

    Persons clients_;
};
