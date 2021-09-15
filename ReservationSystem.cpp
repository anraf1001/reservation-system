#include "ReservationSystem.hpp"

#include <boost/json/src.hpp>
#include <fstream>
#include <iostream>
#include <string>

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

ReservationSystem::ReservationSystem() {
    const fs::path database{"database"};
    if (!fs::is_directory(database)) {
        throw WrongPath{"No database directory"};
    }
    readClientsDatabase(database);
}
