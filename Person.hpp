#pragma once

#include <string>

class Person {
public:
    Person(const std::string& name,
           const std::string& surname,
           const std::string& phoneNum,
           const std::string& email,
           const std::string& pesel,
           bool isVaccinated);

    Person(const std::string& name,
           const std::string& surname,
           const std::string& phoneNum,
           const std::string& email,
           const std::string& pesel)
        : Person{name, surname, phoneNum, email, pesel, false} {}

    void setAsVaccinated() { isVaccinated_ = true; }

    [[nodiscard]] int getAge() const;

    [[nodiscard]] std::string getName() const { return name_; }
    [[nodiscard]] std::string getSurname() const { return surname_; }
    [[nodiscard]] std::string getPhoneNum() const { return phoneNum_; }
    [[nodiscard]] std::string getEmail() const { return email_; }
    [[nodiscard]] std::string getPesel() const { return pesel_; }
    [[nodiscard]] bool isVaccinated() const noexcept { return isVaccinated_; }

private:
    std::string name_;
    std::string surname_;
    std::string phoneNum_;
    std::string email_;
    std::string pesel_;

    bool isVaccinated_;
};
