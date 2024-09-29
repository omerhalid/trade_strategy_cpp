#include <iostream>
#include <string>
#include <vector>
#include "../inc/utils.hpp"
#include "../inc/strategy.hpp"

int main()
{
    // Load environment variables from .env file
    loadEnv();

    // Fetch the API key from environment variables
    const char* apiKey = std::getenv("API_KEY");
    if (!apiKey) {
        std::cerr << "API_KEY not found in environment variables" << std::endl;
        return 1;
    }

    std::cout << "Which stock? " << std::endl;
    std::string stock;
    std::cin >> stock;

    std::string response = fetchMarketData(apiKey, stock);

    std::vector<double> closePrices = parseMarketData(response);

    double shortSMA = Strategy::calculateShortPeriodMovingAverage(closePrices);
    double longSMA = Strategy::calculateLongPeriodMovingAverage(closePrices);
    double rsi = Strategy::calculateRSI(closePrices);

    std::cout << "Short SMA (" << Strategy::shortPeriod << "): " << shortSMA << std::endl;
    std::cout << "Long SMA (" << Strategy::longPeriod << "): " << longSMA << std::endl;
    std::cout << "RSI: " << rsi << std::endl;

    if (shortSMA > longSMA) {
        std::cout << "Moving Average Buy signal" << std::endl;
    } else if (shortSMA < longSMA) {
        std::cout << "Moving Average Sell signal" << std::endl;
    } else {
        std::cout << "Moving Average Hold" << std::endl;
    }

    if (rsi < 30) {
        std::cout << "RSI Buy signal" << std::endl;
    } else if (rsi > 70) {
        std::cout << "RSI Sell signal" << std::endl;
    } else {
        std::cout << "RSI Hold" << std::endl;
    }

    return 0;
}