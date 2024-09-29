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

    movingAverageLogger(shortSMA, longSMA);

    rsiLogger(rsi);

    return 0;
}