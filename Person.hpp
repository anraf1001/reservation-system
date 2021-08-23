#pragma once

#include <string>

class Person {
public:
    Person(const std::string& name,
           const std::string& surname,
           const std::string& phoneNum,
           const std::string& email,
           const std::string& pesel)
        : Person{name, surname, phoneNum, email, pesel, false} {}

    Person(const std::string& name,
           const std::string& surname,
           const std::string& phoneNum,
           const std::string& email,
           const std::string& pesel,
           bool isVaccinated);

    unsigned int getAge() const noexcept;

    std::string getName() const { return name_; }
    std::string getSurname() const { return surname_; }
    std::string getPhoneNum() const { return phoneNum_; }
    std::string getEmail() const { return email_; }
    std::string getPesel() const { return pesel_; }

    bool isVaccinated_;

private:
    std::string name_;
    std::string surname_;
    std::string phoneNum_;
    std::string email_;
    std::string pesel_;
};
