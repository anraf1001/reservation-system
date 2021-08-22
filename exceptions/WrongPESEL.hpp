#pragma once

#include <stdexcept>
#include <string>

struct WrongPESEL : std::invalid_argument {
    WrongPESEL(const std::string& message)
        : std::invalid_argument{message} {}
};
