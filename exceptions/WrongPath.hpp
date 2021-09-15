#pragma once

#include <stdexcept>
#include <string>

struct WrongPath : std::runtime_error {
    WrongPath(const std::string& message)
        : std::runtime_error{message} {}
};
