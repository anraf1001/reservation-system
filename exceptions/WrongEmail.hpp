#pragma once

#include <stdexcept>
#include <string>

struct WrongEmail : std::invalid_argument {
    WrongEmail(const std::string& message)
        : std::invalid_argument{message} {}
};
