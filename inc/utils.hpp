#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

// Function declarations
void loadEnv();
std::string fetchMarketData(const std::string& apiKey, const std::string& symbol);
std::vector<double> parseMarketData(const std::string& jsonData);

#endif // UTILS_HPP