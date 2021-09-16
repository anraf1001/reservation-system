#pragma once

#include <string>
#include <string_view>

class Person {
public:
    Person(std::string_view name,
           std::string_view surname,
           std::string_view phoneNum,
           std::string_view email,
           std::string_view pesel,
           bool isVaccinated);

    Person(std::string_view name,
           std::string_view surname,
           std::string_view phoneNum,
           std::string_view email,
           std::string_view pesel)
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
