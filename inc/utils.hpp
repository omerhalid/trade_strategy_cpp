#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// Function declarations
void loadEnv();
std::string fetchMarketData(const std::string& apiKey, const std::string& symbol);
std::vector<double> parseMarketData(const std::string& jsonData);
void movingAverageLogger(const double shortSMA, const double longSMA);
void rsiLogger(const double rsi);

#endif // UTILS_HPP