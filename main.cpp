#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "../json/json.hpp"
#include "strategy.hpp"
#include <stdlib.h>

// Callback function to handle data received from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to read .env file and set environment variables
void loadEnv() {
    std::ifstream envFile(".env");
    if (!envFile.is_open()) {
        std::cerr << "Failed to open .env file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(envFile, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '=')) {
            std::string value;
            if (std::getline(lineStream, value)) {
                #ifdef _WIN32
                                _putenv_s(key.c_str(), value.c_str());
                #else
                                setenv(key.c_str(), value.c_str(), 1);
                #endif
            }
        }
    }
    envFile.close();
}

std::string fetchMarketData(const std::string& apiKey, const std::string& symbol) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + symbol + "&interval=5min&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // Timeout
        // Disable SSL verification (not recommended for production)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize cURL" << std::endl;
    }

    // Print the response for debugging
    std::cout << "Response: " << readBuffer << std::endl;

    return readBuffer;
}

// Parse the JSON market data and extract close prices
std::vector<double> parseMarketData(const std::string& jsonData) {
    std::vector<double> closePrices;
    try {
        auto json = nlohmann::json::parse(jsonData);
        std::cout << "Processing market data...\n";
        
        for (auto& [timestamp, data] : json["Time Series (5min)"].items()) {
            double closePrice = std::stod(data["4. close"].get<std::string>());
            closePrices.push_back(closePrice);
        }

    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "JSON type error: " << e.what() << std::endl;
    }
    return closePrices;
}

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