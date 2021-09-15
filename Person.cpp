#include "Person.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <regex>

#include "exceptions/WrongEmail.hpp"
#include "exceptions/WrongName.hpp"
#include "exceptions/WrongPESEL.hpp"
#include "exceptions/WrongPhoneNum.hpp"
#include "exceptions/WrongSurname.hpp"

namespace chrono = std::chrono;

const std::regex phoneNumRegex{R"(^(\+\d{2,3})?\s?(\d{3})[-\s]?(\d{3})[-\s]?(\d{3})$)"};

static int calculateYearsFromDate(const std::string& pesel) {
    using Days = chrono::days;
    using Years = chrono::years;

    std::string yearStr = pesel.substr(0, 2);
    std::string monthStr = pesel.substr(2, 2);
    std::string dayStr = pesel.substr(4, 2);

    chrono::day day{static_cast<unsigned>(std::stoi(dayStr))};
    chrono::month month;
    chrono::year year;
    if (std::stoi(monthStr) <= 12) {
        month = chrono::month{static_cast<unsigned>(std::stoi(monthStr))};
        year = chrono::year{1900 + std::stoi(yearStr)};
    } else {
        month = chrono::month{static_cast<unsigned>(std::stoi(monthStr) - 20)};
        year = chrono::year{2000 + std::stoi(yearStr)};
    }

    auto dateOfBirth = chrono::sys_days{year / month / day};
    auto today = chrono::sys_days{chrono::floor<Days>(chrono::system_clock::now())};

    return static_cast<int>(chrono::floor<Years>(today - dateOfBirth).count());
}

static bool isNameValid(const std::string& name) {
    return isupper(name.front()) &&
           std::all_of(name.begin() + 1, name.end(), [](auto letter) {
               return islower(letter);
           });
}

static bool isSurnameValid(const std::string& surname) {
    return isNameValid(surname);
}

static bool isPhoneNumValid(const std::string& phoneNum) {
    return std::regex_match(phoneNum, phoneNumRegex);
}

static bool isEmailValid(const std::string& email) {
    const std::regex emailRegex{R"(^[a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z]+$)"};
    return std::regex_match(email, emailRegex);
}

static int intFromChar(char charToConv) noexcept {
    constexpr char firstDigit = '0';
    return charToConv - firstDigit;
}

static bool isPESELValid(const std::string& pesel) {
    if (pesel.size() != 11 || std::any_of(pesel.cbegin(), pesel.cend(),
                                          [](auto el) {
                                              return !isdigit(el);
                                          })) {
        return false;
    }

    const int controlSum = 9 * intFromChar(pesel[0]) +
                           7 * intFromChar(pesel[1]) +
                           3 * intFromChar(pesel[2]) +
                           1 * intFromChar(pesel[3]) +
                           9 * intFromChar(pesel[4]) +
                           7 * intFromChar(pesel[5]) +
                           3 * intFromChar(pesel[6]) +
                           1 * intFromChar(pesel[7]) +
                           9 * intFromChar(pesel[8]) +
                           7 * intFromChar(pesel[9]);

    const int controlNum = controlSum % 10;

    if (controlNum != intFromChar(pesel.back())) {
        return false;
    }

    return calculateYearsFromDate(pesel) >= 0;
}

static std::string formatPhonenNum(const std::string& phoneNum) {
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

int Person::getAge() const {
    return calculateYearsFromDate(pesel_);
}
