#include "ReservationSystem.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "DisabledSeat.hpp"
#include "StandardSeat.hpp"
#include "VIPSeat.hpp"
#include "exceptions/WrongPath.hpp"

namespace json = boost::json;

static std::shared_ptr<Person> tag_invoke(json::value_to_tag<std::shared_ptr<Person>>, const json::value& jv) {
    const auto& obj = jv.as_object();
    return std::make_shared<Person>(
        json::value_to<std::string>(obj.at("name")),
        json::value_to<std::string>(obj.at("surname")),
        json::value_to<std::string>(obj.at("phoneNum")),
        json::value_to<std::string>(obj.at("email")),
        json::value_to<std::string>(obj.at("pesel")),
        json::value_to<bool>(obj.at("vaccinated")));
}

static Persons tag_invoke(json::value_to_tag<Persons>, const json::value& jv) {
    const auto& arr = jv.as_array();
    Persons ret;
    ret.reserve(arr.size());

    for (const auto& el : arr) {
        ret.push_back(json::value_to<std::shared_ptr<Person>>(el));
    }

    return ret;
}

std::unique_ptr<Seat> ReservationSystem::seatFromJsonValue(const json::value& jv, SeatPtrFactory& ptrFactory) {
    const auto& obj = jv.as_object();

    std::shared_ptr<Person> owner;
    if (!obj.at("owner").is_null()) {
        const auto ownersPesel = json::value_to<std::string>(obj.at("owner"));
        owner = *std::find_if(clients_.begin(), clients_.end(),
                              [&](const std::shared_ptr<Person>& p) {
                                  return p->getPesel() == ownersPesel;
                              });
    }

    const auto seatType = json::value_to<std::string>(obj.at("type"));
    if (seatType == "Standard") {
        return ptrFactory.createSeatPtr<StandardSeat>(owner);
    } else if (seatType == "VIP") {
        return ptrFactory.createSeatPtr<VIPSeat>(owner);
    } else if (seatType == "Disabled") {
        return ptrFactory.createSeatPtr<DisabledSeat>(owner);
    }

    return nullptr;
}

Row ReservationSystem::rowFromJsonValue(const json::value& jv, SeatPtrFactory& ptrFactory) {
    const auto& arr = jv.as_array();
    Row row;
    row.reserve(arr.size());

    for (const auto& el : arr) {
        row.push_back(seatFromJsonValue(el, ptrFactory));
    }

    return row;
}

Stadium ReservationSystem::stadiumFromJson(const json::value& jv, SeatPtrFactory& ptrFactory) {
    const auto& arr = jv.as_array();
    Stadium stadium;
    stadium.reserve(arr.size());

    for (const auto& row : arr) {
        stadium.push_back(rowFromJsonValue(row, ptrFactory));
    }

    return stadium;
}

static json::value readJson(std::istream& is, json::error_code& ec) {
    json::stream_parser parser;
    std::string line;

    while (std::getline(is, line)) {
        parser.write(line, ec);

        if (ec) {
            return nullptr;
        }
    }

    parser.finish(ec);

    if (ec) {
        return nullptr;
    }
    return parser.release();
}

void ReservationSystem::readClientsDatabase(const fs::path& database) {
    fs::path clientsDBFilename{"clients.json"};
    if (!fs::is_regular_file(database / clientsDBFilename)) {
        throw WrongPath{"No clients.json file"};
    }

    std::ifstream clientsFile{database / clientsDBFilename};

    json::value clientsJson;
    json::error_code ec;

    clientsJson = readJson(clientsFile, ec);

    clients_ = json::value_to<Persons>(clientsJson);
}

void ReservationSystem::readSeatsDatabase(const fs::path& database, SeatPtrFactory& ptrFactory) {
    fs::path stadiumDBFilename{"stadium.json"};
    if (!fs::is_regular_file(database / stadiumDBFilename)) {
        throw WrongPath{"No stadium.json file"};
    }

    std::ifstream stadiumFile{database / stadiumDBFilename};

    json::value stadiumJson;
    json::error_code ec;

    stadiumJson = readJson(stadiumFile, ec);

    stadium_ = stadiumFromJson(stadiumJson, ptrFactory);
}

ReservationSystem::ReservationSystem() {
    const fs::path database{"../database"};
    if (!fs::is_directory(database)) {
        throw WrongPath{"No database directory"};
    }
    readClientsDatabase(database);

    SeatPtrFactory ptrFactory;
    readSeatsDatabase(database, ptrFactory);
}

void ReservationSystem::printStadium() const {
    for (const auto& row : stadium_) {
        for (const auto& seat : row) {
            std::cout << *seat << ' ';
        }
        std::cout << '\n';
    }
}
