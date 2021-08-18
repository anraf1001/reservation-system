#pragma once

#include <stdexcept>
#include <string>

struct WrongName : std::invalid_argument {
    WrongName(const std::string& message)
        : std::invalid_argument{message} {}
};
