#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

/**
 * @brief Loads environment variables from the `.env` file.
 */
void loadEnv();

/**
 * @brief Fetches market data for a given stock symbol using an API.
 * @param apiKey The API key for authentication.
 * @param symbol The stock symbol to fetch data for.
 * @return The market data as a JSON string.
 */
std::string fetchMarketData(const std::string& apiKey, const std::string& symbol);

/**
 * @brief Fetches available stocks from the API.
 * @param apiKey The API key for authentication.
 * @return The available stocks as a JSON string.
 */
std::string fetchAvailableStocks(const std::string& apiKey);

/**
 * @brief Parses the market data JSON string and extracts close prices.
 * @param jsonData The JSON data containing stock prices.
 * @return A vector of close prices.
 */
std::vector<double> parseMarketData(const std::string& jsonData);

/**
 * @brief Logs buy, sell, or hold signals based on short and long simple moving averages (SMA).
 * @param shortSMA The short-period SMA.
 * @param longSMA The long-period SMA.
 */
void movingAverageLogger(const double shortSMA, const double longSMA);

/**
 * @brief Logs buy, sell, or hold signals based on the Relative Strength Index (RSI).
 * @param rsi The RSI value.
 */
void rsiLogger(const double rsi);

/**
 * @brief Logs buy, sell, or hold signals based on Bollinger Bands.
 * @param lowerBand The lower Bollinger Band.
 * @param middleBand The middle Bollinger Band (SMA).
 * @param upperBand The upper Bollinger Band.
 * @param lastPrice The most recent stock price.
 */
void bollingerBandsLogger(const double lowerBand, const double middleBand, const double upperBand, const double lastPrice);

/**
 * @brief Loads the menu options for the application.
 */
void loadMenu();

/**
 * @brief Fetches the list of available stocks.
 * @return A vector containing stock symbols.
 */
std::vector<std::string> getAvailableStocks();

/**
 * @brief Parses the JSON response and extracts available stock symbols.
 * @param jsonData The JSON data containing stock information.
 * @return A vector of stock symbols.
 */
std::vector<std::string> parseAvailableStocks(const std::string& jsonData);

#endif // UTILS_HPP
