#include "../inc/utils.hpp"
#include "../inc/strategy.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include "../json/json.hpp"

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
                std::string envVar = key + "=" + value;
                putenv(envVar.c_str());
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

std::string fetchAvailableStocks(const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        // Fetching a list of available stocks from Alpha Vantage or similar API
        std::string url = "https://www.alphavantage.co/query?function=LISTING_STATUS&apikey=" + apiKey;
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

    // Print the raw response for debugging
    std::cout << "Raw API Response: " << readBuffer << std::endl;

    return readBuffer;
}

// Parse the JSON market data and extract close prices
std::vector<double> parseMarketData(const std::string& jsonData) {
    std::vector<double> closePrices;
    try {
        auto json = nlohmann::json::parse(jsonData);
        std::cout << "Processing market data...\n";
        std::cout << "\n";
        
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

std::vector<std::string> parseAvailableStocks(const std::string& jsonData) {
    std::vector<std::string> stockSymbols;
    try {
        auto json = nlohmann::json::parse(jsonData);
        std::cout << "Processing available stocks...\n";
        std::cout << "\n";
        
        if (json.contains("data")) {
            for (auto& stock : json["data"]) {
                std::string symbol = stock["symbol"].get<std::string>();
                stockSymbols.push_back(symbol);
            }
        } else {
            std::cerr << "Unexpected JSON format: 'data' field not found" << std::endl;
        }

    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "JSON type error: " << e.what() << std::endl;
    }
    return stockSymbols;
}

std::vector<std::string> getAvailableStocks() {
    const char* apiKey = std::getenv("API_KEY");
    if (apiKey == nullptr) {
        std::cerr << "API_KEY not found in environment variables" << std::endl;
        return {};
    }

    std::string response = fetchAvailableStocks(apiKey);
    return parseAvailableStocks(response);
}

void movingAverageLogger(const double shortSMA, const double longSMA)
{
    if (shortSMA > longSMA) {
        std::cout << "Moving Average Buy signal" << std::endl;
    } else if (shortSMA < longSMA) {
        std::cout << "Moving Average Sell signal" << std::endl;
    } else {
        std::cout << "Moving Average Hold" << std::endl;
    }
}

void rsiLogger(const double rsi)
{
    if (rsi < 30) {
        std::cout << "RSI Buy signal" << std::endl;
    } else if (rsi > 70) {
        std::cout << "RSI Sell signal" << std::endl;
    } else {
        std::cout << "RSI Hold" << std::endl;
    }
}

void bollingerBandsLogger(const double lowerBand, const double middleBand, const double upperBand, const double lastPrice)
{
    if (lastPrice < lowerBand) {
        std::cout << "Bollinger Bands Buy signal" << std::endl;
    } else if (lastPrice > upperBand) {
        std::cout << "Bollinger Bands Sell signal" << std::endl;
    } else {
        std::cout << "Bollinger Bands Hold" << std::endl;
    }
}

void loadMenu() {
    std::map<int, std::string> menuOptions = {
        {1, "Display available stocks"},
        {2, "Enter a stock name"},
        {3, "Exit"}
    };

    int choice;
    const char* apiKey = std::getenv("API_KEY");
    if (apiKey == nullptr) {
        std::cerr << "API_KEY not found in environment variables" << std::endl;
        return;
    }

    while (true) {
        std::cout << "\nMenu Options:\n";
        for (const auto& option : menuOptions) {
            std::cout << option.first << ". " << option.second << "\n";
        }
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::vector<std::string> stocks = getAvailableStocks();
                std::cout << "Available Stocks:\n";
                for (const auto& stock : stocks) {
                    std::cout << "- " << stock << "\n";
                }
                break;
            }
            case 2: {
                    std::string stock;
                    std::cout << "Enter stock name: ";
                    std::cin >> stock;

                    std::string response = fetchMarketData(apiKey, stock);
                    std::vector<double> closePrices = parseMarketData(response);

                    double shortSMA = Strategy::calculateShortPeriodMovingAverage(closePrices);
                    double longSMA = Strategy::calculateLongPeriodMovingAverage(closePrices);
                    double rsi = Strategy::calculateRSI(closePrices);
                    auto [lowerBand, middleBand, upperBand] = Strategy::calculateBollingerBands(closePrices);

                    std::cout << "Short SMA: " << shortSMA << "\n";
                    std::cout << "Long SMA: " << longSMA << "\n";
                    std::cout << "RSI: " << rsi << "\n";
                    std::cout << "Bollinger Bands: Lower=" << lowerBand << ", Middle=" << middleBand << ", Upper=" << upperBand << "\n";

                    movingAverageLogger(shortSMA, longSMA);
                    rsiLogger(rsi);
                    bollingerBandsLogger(lowerBand, middleBand, upperBand, closePrices.back()); // Pass the latest price
                    break;
                }
            case 3:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
