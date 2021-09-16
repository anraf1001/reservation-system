#include <gtest/gtest.h>

#include "Person.hpp"

#include <tuple>
#include <string_view>

#include "exceptions/WrongEmail.hpp"
#include "exceptions/WrongName.hpp"
#include "exceptions/WrongPESEL.hpp"
#include "exceptions/WrongPhoneNum.hpp"
#include "exceptions/WrongSurname.hpp"

constexpr std::string_view rightName = "Jan";
constexpr std::string_view rightSurname = "Kowalski";
constexpr std::string_view rightPhoneNum = "123456789";
constexpr std::string_view rightEmail = "test@email.com";
constexpr std::string_view rightPESEL = "20271854937";

struct wrongNameTest : ::testing::TestWithParam<std::string> {};
struct wrongSurnameTest : ::testing::TestWithParam<std::string> {};
struct rightPhoneNumTest : ::testing::TestWithParam<std::tuple<std::string, std::string>> {};
struct wrongPhoneNumTest : ::testing::TestWithParam<std::string> {};
struct wrongEmailTest : ::testing::TestWithParam<std::string> {};
struct wrongPESELTest : ::testing::TestWithParam<std::string> {};

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

TEST_P(wrongEmailTest, shouldThrowExceptionForWrongEmail) {
    auto wrongEmail = GetParam();
    ASSERT_THROW(Person(rightName, rightSurname, rightPhoneNum, wrongEmail, rightPESEL), WrongEmail);
}

TEST_P(wrongPESELTest, shouldThrowExceptionForWrongPESEL) {
    auto wrongPESEL = GetParam();
    ASSERT_THROW(Person(rightName, rightSurname, rightPhoneNum, rightEmail, wrongPESEL), WrongPESEL);
}

TEST(getAgeTest, shouldCalculateAgeFromPESELNum) {
    constexpr std::string_view pesel1900 = "78051654912";
    constexpr unsigned int pesel1900Age = 43;
    constexpr std::string_view pesel2000 = "20271854937";
    constexpr unsigned int pesel2000Age = 1;

    Person person1{rightName, rightSurname, rightPhoneNum, rightEmail, pesel1900};
    ASSERT_EQ(person1.getAge(), pesel1900Age);

    Person person2{rightName, rightSurname, rightPhoneNum, rightEmail, pesel2000};
    ASSERT_EQ(person2.getAge(), pesel2000Age);
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

INSTANTIATE_TEST_CASE_P(
    PersonTest,
    wrongEmailTest,
    ::testing::Values("sagdgdg",
                      "sndj@!$%.com",
                      "jdh26@dlk",
                      "lsdko@kdocl.90",
                      "_!@gmail.com",
                      ""));

INSTANTIATE_TEST_CASE_P(
    PersonTest,
    wrongPESELTest,
    ::testing::Values("00211009695",
                      "54876425897",
                      "sdffg8556",
                      ""));
