#include <iostream>
#include <string>
#include <vector>
#include "utils.hpp"
#include "strategy.hpp"

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

    std::cout << "Short SMA (" << Strategy::shortPeriod << "): " << shortSMA << std::endl;
    std::cout << "Long SMA (" << Strategy::longPeriod << "): " << longSMA << std::endl;

    if (shortSMA > longSMA) {
        std::cout << "Buy signal" << std::endl;
    } else if (shortSMA < longSMA) {
        std::cout << "Sell signal" << std::endl;
    } else {
        std::cout << "Hold" << std::endl;
    }

    return 0;
}