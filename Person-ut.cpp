#include <gtest/gtest.h>

#include "Person.hpp"

#include <tuple>

#include "exceptions/WrongName.hpp"
#include "exceptions/WrongPhoneNum.hpp"
#include "exceptions/WrongSurname.hpp"

constexpr const char* rightName = "Jan";
constexpr const char* rightSurname = "Kowalski";
constexpr const char* rightPhoneNum = "123456789";
constexpr const char* rightEmail = "test@email.com";
constexpr const char* rightPESEL = "98564726982";

struct wrongNameTest : ::testing::TestWithParam<std::string> {};
struct wrongSurnameTest : ::testing::TestWithParam<std::string> {};
struct rightPhoneNumTest : ::testing::TestWithParam<std::tuple<std::string, std::string>> {};
struct wrongPhoneNumTest : ::testing::TestWithParam<std::string> {};

TEST_P(wrongNameTest, shouldThrowExceptionForWrongName) {
    auto wrongName = GetParam();
    ASSERT_THROW(Person(wrongName, rightSurname, rightPhoneNum, rightEmail, rightPESEL), WrongName);
}

TEST_P(wrongSurnameTest, shouldThrowExceptionForWrongSurname) {
    auto wrongSurname = GetParam();
    ASSERT_THROW(Person(rightName, wrongSurname, rightPhoneNum, rightEmail, rightPESEL), WrongSurname);
}

TEST_P(rightPhoneNumTest, shouldShouldFormatPhoneNum) {
    auto [phoneNum, formattedNum] = GetParam();
    ASSERT_NO_THROW(Person(rightName, rightSurname, phoneNum, rightEmail, rightPESEL));

    Person person{rightName, rightSurname, phoneNum, rightEmail, rightPESEL};
    ASSERT_EQ(person.getPhoneNum(), formattedNum);
}

TEST_P(wrongPhoneNumTest, shouldThrowExceptionForWrongPhoneNum) {
    auto wrongPhoneNum = GetParam();
    ASSERT_THROW(Person(rightName, rightSurname, wrongPhoneNum, rightEmail, rightPESEL), WrongPhoneNum);
}

INSTANTIATE_TEST_CASE_P(
    PersonTest,
    wrongNameTest,
    ::testing::Values("jan",
                      "jAn",
                      "Jan3",
                      ""));

INSTANTIATE_TEST_CASE_P(
    PersonTest,
    wrongSurnameTest,
    ::testing::Values("kowalski",
                      "kOwaLski",
                      "6Kowalski4",
                      ""));

INSTANTIATE_TEST_CASE_P(
    PersonTest,
    rightPhoneNumTest,
    ::testing::Values(
        std::make_tuple("123456789", "123456789"),
        std::make_tuple("123-456-789", "123456789"),
        std::make_tuple("123 456 789", "123456789"),
        std::make_tuple("+48123456789", "123456789"),
        std::make_tuple("+48 123456789", "123456789"),
        std::make_tuple("+48123-456-789", "123456789"),
        std::make_tuple("+48123 456 789", "123456789"),
        std::make_tuple("+48 123 456 789", "123456789"),
        std::make_tuple("+48 123-456-789", "123456789")));

INSTANTIATE_TEST_CASE_P(
    PersonTest,
    wrongPhoneNumTest,
    ::testing::Values("25648",
                      "+48 5876sd6w9",
                      "+6985469875369458",
                      "874236518952",
                      "-48 123-456-789",
                      ""));
