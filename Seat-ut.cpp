#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "DisabledSeat.hpp"
#include "Seat.hpp"
#include "StandardSeat.hpp"
#include "VIPSeat.hpp"

constexpr unsigned int standardID = 123;
constexpr unsigned int vipID = 456;
constexpr unsigned int disabledID = 789;

struct SeatTests : ::testing::Test {
    SeatTests() {
        seatsVec.push_back(std::make_shared<StandardSeat>(standardID));
        seatsVec.push_back(std::make_shared<VIPSeat>(vipID));
        seatsVec.push_back(std::make_shared<DisabledSeat>(disabledID));
    }

    std::vector<std::shared_ptr<Seat>> seatsVec;
};

TEST_F(SeatTests, shouldCreateDifferentTypesOfSeats) {
    EXPECT_EQ(seatsVec[0]->getID(), standardID);
    EXPECT_EQ(seatsVec[1]->getID(), vipID);
    EXPECT_EQ(seatsVec[2]->getID(), disabledID);

    EXPECT_FALSE(seatsVec[0]->isTaken());
    EXPECT_FALSE(seatsVec[1]->isTaken());
    EXPECT_FALSE(seatsVec[2]->isTaken());

    EXPECT_EQ(seatsVec[0]->getSymbol(), standardSeatSymbol);
    EXPECT_EQ(seatsVec[1]->getSymbol(), vipSeatSymbol);
    EXPECT_EQ(seatsVec[2]->getSymbol(), disabledSeatSymbol);
}

TEST_F(SeatTests, shouldTakeSeats) {
    constexpr const char* rightName = "Jan";
    constexpr const char* rightSurname = "Kowalski";
    constexpr const char* rightPhoneNum = "123456789";
    constexpr const char* rightEmail = "test@email.com";
    constexpr const char* rightPESEL = "20271854937";

    auto person1Ptr = std::make_shared<Person>(rightName, rightSurname, rightPhoneNum, rightEmail, rightPESEL);

    for (auto& seat : seatsVec) {
        seat->take(person1Ptr);
    }

    for (const auto& seat : seatsVec) {
        EXPECT_TRUE(seat->isTaken());
        EXPECT_EQ(seat->getOwner().get(), person1Ptr.get());
    }

    auto person2Ptr = std::make_shared<Person>(rightName, rightSurname, rightPhoneNum, rightEmail, rightPESEL);
    for (auto& seat : seatsVec) {
        seat->take(person2Ptr);
    }

    for (const auto& seat : seatsVec) {
        EXPECT_TRUE(seat->isTaken());
        EXPECT_EQ(seat->getOwner().get(), person2Ptr.get());
    }
}

TEST_F(SeatTests, shouldFreeSeats) {
    for (auto& seat : seatsVec) {
        seat->free();
    }

    for (const auto& seat : seatsVec) {
        EXPECT_FALSE(seat->isTaken());
    }
}
