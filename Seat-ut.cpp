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
constexpr bool standardStatus = false;
constexpr bool vipStatus = true;
constexpr bool disabledStatus = false;

struct SeatTests : ::testing::Test {
    SeatTests() {
        seatsVec.push_back(std::make_shared<StandardSeat>(standardID, standardStatus));
        seatsVec.push_back(std::make_shared<VIPSeat>(vipID, vipStatus));
        seatsVec.push_back(std::make_shared<DisabledSeat>(disabledID, disabledStatus));
    }

    std::vector<std::shared_ptr<Seat>> seatsVec;
};

TEST_F(SeatTests, shouldCreateDifferentTypesOfSeats) {
    EXPECT_EQ(seatsVec[0]->getID(), standardID);
    EXPECT_EQ(seatsVec[1]->getID(), vipID);
    EXPECT_EQ(seatsVec[2]->getID(), disabledID);

    EXPECT_EQ(seatsVec[0]->isTaken(), standardStatus);
    EXPECT_EQ(seatsVec[1]->isTaken(), vipStatus);
    EXPECT_EQ(seatsVec[2]->isTaken(), disabledStatus);

    EXPECT_EQ(seatsVec[0]->getSymbol(), standardSeatSymbol);
    EXPECT_EQ(seatsVec[1]->getSymbol(), vipSeatSymbol);
    EXPECT_EQ(seatsVec[2]->getSymbol(), disabledSeatSymbol);
}

TEST_F(SeatTests, shouldTakeSeats) {
    for (auto& seat : seatsVec) {
        seat->take();
    }

    for (const auto& seat : seatsVec) {
        EXPECT_TRUE(seat->isTaken());
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
