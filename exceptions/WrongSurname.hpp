#pragma once

#include <stdexcept>
#include <string>

struct WrongSurname : std::invalid_argument {
    WrongSurname(const std::string& message)
        : std::invalid_argument{message} {}
};
