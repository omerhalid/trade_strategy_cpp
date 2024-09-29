#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// Function declarations
void loadEnv();
std::string fetchMarketData(const std::string& apiKey, const std::string& symbol);
std::string fetchAvailableStocks(const std::string& apiKey);
std::vector<double> parseMarketData(const std::string& jsonData);
void movingAverageLogger(const double shortSMA, const double longSMA);
void rsiLogger(const double rsi);
void bollingerBandsLogger(const double lowerBand, const double middleBand, const double upperBand, const double lastPrice);
void loadMenu();
std::vector<std::string> getAvailableStocks();
std::vector<std::string> parseAvailableStocks(const std::string& jsonData);

#endif // UTILS_HPP