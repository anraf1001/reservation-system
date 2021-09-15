#include "ReservationSystem.hpp"

#include <boost/json/src.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "exceptions/WrongPath.hpp"

namespace json = boost::json;
namespace fs = std::filesystem;

json::value readJson(std::istream& is, json::error_code& ec) {
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

void readClientsDatabase(const fs::path& database) {
    fs::path clientsDBFilename{"clients.json"};
    if (!fs::is_regular_file(database / clientsDBFilename)) {
        throw WrongPath{"No clients.json file"};
    }
    std::ifstream clientsFile{database / clientsDBFilename};

    json::value clientsJson;
    json::error_code ec;

    clientsJson = readJson(clientsFile, ec);
}

ReservationSystem::ReservationSystem() {
    const fs::path database{"database"};
    if (!fs::is_directory(database)) {
        throw WrongPath{"No database directory"};
    }
    readClientsDatabase(database);
}
