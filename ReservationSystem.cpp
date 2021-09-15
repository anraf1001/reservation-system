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

constexpr const char* clientsFilename = "clients.json";
constexpr const char* stadiumFilename = "stadium.json";

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

static void tag_invoke(json::value_from_tag, json::value& jv, const std::shared_ptr<Person>& person) {
    jv = {{"pesel", person->getPesel()},
          {"name", person->getName()},
          {"surname", person->getSurname()},
          {"phoneNum", person->getPhoneNum()},
          {"email", person->getEmail()},
          {"vaccinated", person->isVaccinated()}};
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

void ReservationSystem::readClientsDatabase() {
    fs::path clientsDBFilename{clientsFilename};
    if (!fs::is_regular_file(dbDirectory_ / clientsDBFilename)) {
        throw WrongPath{"No clients.json file"};
    }

    std::ifstream clientsFile{dbDirectory_ / clientsDBFilename};

    json::value clientsJson;
    json::error_code ec;

    clientsJson = readJson(clientsFile, ec);

    clients_ = json::value_to<Persons>(clientsJson);
}

void ReservationSystem::readSeatsDatabase(SeatPtrFactory& ptrFactory) {
    fs::path stadiumDBFilename{stadiumFilename};
    if (!fs::is_regular_file(dbDirectory_ / stadiumDBFilename)) {
        throw WrongPath{"No stadium.json file"};
    }

    std::ifstream stadiumFile{dbDirectory_ / stadiumDBFilename};

    json::value stadiumJson;
    json::error_code ec;

    stadiumJson = readJson(stadiumFile, ec);

    stadium_ = stadiumFromJson(stadiumJson, ptrFactory);
}

ReservationSystem::ReservationSystem() {
    if (!fs::is_directory(dbDirectory_)) {
        throw WrongPath{"No database directory"};
    }
    readClientsDatabase();

    SeatPtrFactory ptrFactory;
    readSeatsDatabase(ptrFactory);
}

static void pretty_print(std::ostream& os, const json::value& jv, std::string& indent);

static void printingObject(std::ostream& os, const json::object& obj, std::string& indent) {
    os << "{\n";
    indent.append(4, ' ');
    if (!obj.empty()) {
        auto it = obj.begin();
        for (;;) {
            os << indent << json::serialize(it->key()) << ": ";
            pretty_print(os, it->value(), indent);
            if (++it == obj.end())
                break;
            os << ",\n";
        }
    }
    os << "\n";
    indent.resize(indent.size() - 4);
    os << indent << "}";
}

static void printingArray(std::ostream& os, const json::array& arr, std::string& indent) {
    os << "[\n";
    indent.append(4, ' ');
    if (!arr.empty()) {
        auto it = arr.begin();
        for (;;) {
            os << indent;
            pretty_print(os, *it, indent);
            if (++it == arr.end())
                break;
            os << ",\n";
        }
    }
    os << "\n";
    indent.resize(indent.size() - 4);
    os << indent << "]";
}

static void printingValue(std::ostream& os, const json::value& jv, std::string& indent) {
    switch (jv.kind()) {
    case json::kind::object: {
        printingObject(os, jv.get_object(), indent);
        break;
    }

    case json::kind::array: {
        printingArray(os, jv.get_array(), indent);
        break;
    }

    case json::kind::string:
        os << json::serialize(jv.get_string());
        break;

    case json::kind::uint64:
        os << jv.get_uint64();
        break;

    case json::kind::int64:
        os << jv.get_int64();
        break;

    case json::kind::double_:
        os << jv.get_double();
        break;

    case json::kind::bool_:
        if (jv.get_bool())
            os << "true";
        else
            os << "false";
        break;

    case json::kind::null:
        os << "null";
        break;
    }
}

static void pretty_print(std::ostream& os, const json::value& jv, std::string& indent) {
    printingValue(os, jv, indent);
}

static void printJson(std::ostream& os, const json::value& jv) {
    std::string indent{};

    printingValue(os, jv, indent);

    if (indent.empty())
        os << "\n";
}

void ReservationSystem::saveClientsDatabase() {
    fs::path actualClientsFile{clientsFilename};
    fs::path backupClientsFile{std::string{clientsFilename} + ".old"};
    fs::copy_file(dbDirectory_ / actualClientsFile, dbDirectory_ / backupClientsFile, fs::copy_options::overwrite_existing);

    std::ofstream outputFile{dbDirectory_ / actualClientsFile, std::ios::trunc};

    auto jv = json::value_from(clients_);
    printJson(outputFile, jv);

    fs::remove(dbDirectory_ / backupClientsFile);
}

void ReservationSystem::saveSeatsDatabase() {
    fs::path currentStadiumFile{stadiumFilename};
    fs::path backupStadiumFile{std::string{stadiumFilename} + ".old"};
    fs::copy_file(dbDirectory_ / currentStadiumFile, dbDirectory_ / backupStadiumFile, fs::copy_options::overwrite_existing);

    std::ofstream outputFile{dbDirectory_ / currentStadiumFile, std::ios::trunc};

    auto jv = json::value_from(stadium_);

    fs::remove(dbDirectory_ / backupStadiumFile);
}

ReservationSystem::~ReservationSystem() {
    saveClientsDatabase();
    saveSeatsDatabase();
}

void ReservationSystem::printStadium() const {
    for (const auto& row : stadium_) {
        for (const auto& seat : row) {
            std::cout << *seat << ' ';
        }
        std::cout << '\n';
    }
}
