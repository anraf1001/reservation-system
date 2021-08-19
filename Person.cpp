#include "Person.hpp"

#include <algorithm>
#include <cctype>
#include <regex>

#include "exceptions/WrongName.hpp"
#include "exceptions/WrongPhoneNum.hpp"
#include "exceptions/WrongSurname.hpp"

const std::regex phoneNumRegex{R"((\+\d{2,3})?\s?(\d{3})[-\s]?(\d{3})[-\s]?(\d{3}))"};

bool isNameValid(const std::string& name) {
    return isupper(name.front()) &&
           std::all_of(name.begin() + 1, name.end(), [](auto letter) {
               return islower(letter);
           });
}

bool isSurnameValid(const std::string& surname) {
    return isNameValid(surname);
}

bool isPhoneNumValid(const std::string& phoneNum) {
    return std::regex_match(phoneNum, phoneNumRegex);
}

std::string formatPhonenNum(const std::string& phoneNum) {
    std::smatch matches;
    std::regex_search(phoneNum, matches, phoneNumRegex);

    std::string formattedPhoneNum = matches[2];
    formattedPhoneNum += matches[3];
    formattedPhoneNum += matches[4];

    return formattedPhoneNum;
}

Person::Person(const std::string& name,
               const std::string& surname,
               const std::string& phoneNum,
               const std::string& email,
               const std::string& pesel,
               bool isVaccinated)
    : isVaccinated_{isVaccinated} {
    if (!isNameValid(name)) {
        std::string message{name};
        message += " is not a valid name";
        throw WrongName{message};
    }

    if (!isSurnameValid(surname)) {
        std::string message{surname};
        message += " is not a valid surname";
        throw WrongSurname{message};
    }

    if (!isPhoneNumValid(phoneNum)) {
        std::string message{phoneNum};
        message += " is not a valid phone number";
        throw WrongPhoneNum{message};
    }

    name_ = name;
    surname_ = surname;
    phoneNum_ = formatPhonenNum(phoneNum);
    email_ = email;
    pesel_ = pesel;
}
