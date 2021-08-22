#include "Person.hpp"

#include <algorithm>
#include <cctype>
#include <regex>

#include "exceptions/WrongEmail.hpp"
#include "exceptions/WrongName.hpp"
#include "exceptions/WrongPESEL.hpp"
#include "exceptions/WrongPhoneNum.hpp"
#include "exceptions/WrongSurname.hpp"

const std::regex phoneNumRegex{R"(^(\+\d{2,3})?\s?(\d{3})[-\s]?(\d{3})[-\s]?(\d{3})$)"};

constexpr char firstDigit = '0';

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

bool isEmailValid(const std::string& email) {
    const std::regex emailRegex{R"(^[a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z]+$)"};
    return std::regex_match(email, emailRegex);
}

bool isPESELValid(const std::string& pesel) {
    if (pesel.size() != 11 || std::any_of(pesel.cbegin(), pesel.cend(),
                                          [](auto el) {
                                              return !isdigit(el);
                                          })) {
        return false;
    }

    const int controlSum = 9 * static_cast<int>(pesel[0] - firstDigit) +
                           7 * static_cast<int>(pesel[1] - firstDigit) +
                           3 * static_cast<int>(pesel[2] - firstDigit) +
                           1 * static_cast<int>(pesel[3] - firstDigit) +
                           9 * static_cast<int>(pesel[4] - firstDigit) +
                           7 * static_cast<int>(pesel[5] - firstDigit) +
                           3 * static_cast<int>(pesel[6] - firstDigit) +
                           1 * static_cast<int>(pesel[7] - firstDigit) +
                           9 * static_cast<int>(pesel[8] - firstDigit) +
                           7 * static_cast<int>(pesel[9] - firstDigit);

    const int controlNum = controlSum % 10;

    return controlNum == static_cast<int>(pesel.back() - firstDigit);
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

    if (!isEmailValid(email)) {
        std::string message{email};
        message += " is not a valid email address";
        throw WrongEmail{message};
    }

    if (!isPESELValid(pesel)) {
        std::string message{pesel};
        message += " is not a valid pesel number";
        throw WrongPESEL{message};
    }

    name_ = name;
    surname_ = surname;
    phoneNum_ = formatPhonenNum(phoneNum);
    email_ = email;
    pesel_ = pesel;
}
