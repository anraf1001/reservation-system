#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "DisabledSeat.hpp"
#include "Seat.hpp"
#include "StandardSeat.hpp"
#include "VIPSeat.hpp"

TEST(SeatTests, shouldCreateDifferentTypesOfSeats) {
    constexpr unsigned int standardID = 123;
    constexpr unsigned int vipID = 456;
    constexpr unsigned int disabledID = 789;
    constexpr bool standardStatus = false;
    constexpr bool vipStatus = true;
    constexpr bool disabledStatus = false;

    std::vector<std::shared_ptr<Seat>> seatsVec{
        std::make_shared<StandardSeat>(standardID, standardStatus),
        std::make_shared<VIPSeat>(vipID, vipStatus),
        std::make_shared<DisabledSeat>(disabledID, disabledStatus)};

    ASSERT_EQ(seatsVec[0]->getID(), standardID);
    ASSERT_EQ(seatsVec[1]->getID(), vipID);
    ASSERT_EQ(seatsVec[2]->getID(), disabledID);

    ASSERT_EQ(seatsVec[0]->isTaken(), standardStatus);
    ASSERT_EQ(seatsVec[1]->isTaken(), vipStatus);
    ASSERT_EQ(seatsVec[2]->isTaken(), disabledStatus);

    ASSERT_EQ(seatsVec[0]->getSymbol(), standardSeatSymbol);
    ASSERT_EQ(seatsVec[1]->getSymbol(), vipSeatSymbol);
    ASSERT_EQ(seatsVec[2]->getSymbol(), disabledSeatSymbol);
}
