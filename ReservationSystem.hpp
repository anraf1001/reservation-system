#pragma once

#include <boost/json.hpp>
#include <filesystem>
#include <memory>
#include <vector>

#include "Person.hpp"
#include "Seat.hpp"
#include "SeatPtrFactory.hpp"

namespace fs = std::filesystem;
namespace json = boost::json;

using Persons = std::vector<std::shared_ptr<Person>>;
using Row = std::vector<std::unique_ptr<Seat>>;
using Stadium = std::vector<Row>;

class ReservationSystem {
public:
    ReservationSystem();

    void printStadium() const;

private:
    void readClientsDatabase(const fs::path& database);
    void readSeatsDatabase(const fs::path& database, SeatPtrFactory& ptrFactory);

    std::unique_ptr<Seat> seatFromJsonValue(const json::value& jv, SeatPtrFactory& ptrFactory);
    Row rowFromJsonValue(const json::value& jv, SeatPtrFactory& ptrFactory);
    Stadium stadiumFromJson(const json::value& jv, SeatPtrFactory& ptrFactory);

    Stadium stadium_;
    Persons clients_;
};
