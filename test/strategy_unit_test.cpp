#include <gtest/gtest.h>
#include "../inc/strategy.hpp"
#include "../inc/utils.hpp"
#include <vector>
#include <string>
#include <cstdlib>

// Helper function to set environment variables for testing
void setEnv(const std::string& key, const std::string& value) {
    std::string envVar = key + "=" + value;
    putenv(envVar.c_str());
}

// Test fixture class for Strategy tests
class StrategyTest : public ::testing::Test {
protected:
    std::vector<double> prices;

    void SetUp() override {
        // Common setup code for all tests
        prices = {1.0, 2.0, 3.0, 4.0, 5.0};
    }

    void TearDown() override {
        // Common teardown code for all tests
    }
};

TEST_F(StrategyTest, CalculateShortPeriodMovingAverage) {
    double result = Strategy::calculateShortPeriodMovingAverage(prices);
    EXPECT_DOUBLE_EQ(result, 4.0);  // Assuming shortPeriod is 2
}

TEST_F(StrategyTest, CalculateLongPeriodMovingAverage) {
    double result = Strategy::calculateLongPeriodMovingAverage(prices);
    EXPECT_DOUBLE_EQ(result, 3.0);  // Assuming longPeriod is 5
}

TEST_F(StrategyTest, CalculateRSI) {
    std::vector<double> rsiPrices = {1.0, 2.0, 1.5, 2.5, 2.0, 3.0, 2.5};
    double result = Strategy::calculateRSI(rsiPrices, 5);
    EXPECT_NEAR(result, 50.0, 0.1);  // Example expected value
}

TEST_F(StrategyTest, CalculateBollingerBands) {
    std::vector<double> bbPrices = {1.0, 2.0, 1.5, 2.5, 2.0, 3.0, 2.5};
    auto [lowerBand, middleBand, upperBand] = Strategy::calculateBollingerBands(bbPrices, 5, 2.0);
    EXPECT_NEAR(lowerBand, 1.0, 0.1);  // Example expected value
    EXPECT_NEAR(middleBand, 2.0, 0.1);  // Example expected value
    EXPECT_NEAR(upperBand, 3.0, 0.1);  // Example expected value
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}