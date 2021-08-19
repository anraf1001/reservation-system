#include <gtest/gtest.h>

#include "Person.hpp"

#include "exceptions/WrongName.hpp"
#include "exceptions/WrongSurname.hpp"

constexpr const char* rightName = "Jan";
constexpr const char* rightSurname = "Kowalski";
constexpr const char* rightPhoneNum = "123456789";
constexpr const char* rightEmail = "test@email.com";
constexpr const char* rightPESEL = "98564726982";

TEST(PersonTest, shouldThrowExceptionForWrongName) {
    constexpr const char* wrongName1 = "jan";
    ASSERT_THROW(Person(wrongName1, rightSurname, rightPhoneNum, rightEmail, rightPESEL), WrongName);

    constexpr const char* wrongName2 = "jAn";
    ASSERT_THROW(Person(wrongName2, rightSurname, rightPhoneNum, rightEmail, rightPESEL), WrongName);

    constexpr const char* wrongName3 = "Jan3";
    ASSERT_THROW(Person(wrongName3, rightSurname, rightPhoneNum, rightEmail, rightPESEL), WrongName);

    constexpr const char* wrongName4 = "";
    ASSERT_THROW(Person(wrongName4, rightSurname, rightPhoneNum, rightEmail, rightPESEL), WrongName);
}

TEST(PersonTest, shouldThrowExceptionForWrongSurname) {
    constexpr const char* wrongSurname1 = "kowalski";
    ASSERT_THROW(Person(rightName, wrongSurname1, rightPhoneNum, rightEmail, rightPESEL), WrongSurname);

    constexpr const char* wrongSurname2 = "kOwaLski";
    ASSERT_THROW(Person(rightName, wrongSurname2, rightPhoneNum, rightEmail, rightPESEL), WrongSurname);

    constexpr const char* wrongSurname3 = "6Kowalski4";
    ASSERT_THROW(Person(rightName, wrongSurname3, rightPhoneNum, rightEmail, rightPESEL), WrongSurname);

    constexpr const char* wrongSurname4 = "";
    ASSERT_THROW(Person(rightName, wrongSurname4, rightPhoneNum, rightEmail, rightPESEL), WrongSurname);
}
