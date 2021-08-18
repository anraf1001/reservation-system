#pragma once

#include <string>

class Person {
public:
    Person(const std::string& name,
           const std::string& surname,
           const std::string& phoneNum,
           const std::string& email,
           const std::string& pesel);

    Person(const std::string& name,
           const std::string& surname,
           const std::string& phoneNum,
           const std::string& email,
           const std::string& pesel,
           bool isVaccinated);

    bool isVaccinated_ = false;

private:
    std::string name_;
    std::string surname_;
    std::string phoneNum_;
    std::string email_;
    std::string pesel_;
};
