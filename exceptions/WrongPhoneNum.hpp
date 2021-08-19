#pragma once

#include <stdexcept>
#include <string>

struct WrongPhoneNum : std::invalid_argument {
    WrongPhoneNum(const std::string& message)
        : std::invalid_argument{message} {}
};
