#include "Person.hpp"

#include <algorithm>
#include <cctype>

#include "exceptions/WrongName.hpp"
#include "exceptions/WrongSurname.hpp"

bool isNameValid(const std::string& name) {
    return isupper(name.front()) &&
           std::all_of(name.begin() + 1, name.end(), [](auto letter) {
               return islower(letter);
           });
}

bool isSurnameValid(const std::string surname) {
    return isNameValid(surname);
}

Person::Person(const std::string& name,
               const std::string& surname,
               const std::string& phoneNum,
               const std::string& email,
               const std::string& pesel,
               bool isVaccinated)
    : isVaccinated_{isVaccinated} {
    if (!isNameValid(name)) {
        throw WrongName{name + " is not a valid name"};
    }

    if (!isSurnameValid(surname)) {
        throw WrongSurname{surname + " is not a valid surname"};
    }

    name_ = name;
    surname_ = surname;
    phoneNum_ = phoneNum;
    email_ = email;
    pesel_ = pesel;
}
