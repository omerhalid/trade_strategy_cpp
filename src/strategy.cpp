#include "../inc/strategy.hpp"
#include <cmath>
#include <numeric>

// Calculate short period moving average
double Strategy::calculateShortPeriodMovingAverage(const std::vector<double>& prices) {
    if (prices.size() < shortPeriod) return 0.0;
    double sum = std::accumulate(prices.end() - shortPeriod, prices.end(), 0.0);
    return sum / shortPeriod;
}

// Calculate long period moving average
double Strategy::calculateLongPeriodMovingAverage(const std::vector<double>& prices) {
    if (prices.size() < longPeriod) return 0.0;
    double sum = std::accumulate(prices.end() - longPeriod, prices.end(), 0.0);
    return sum / longPeriod;
}

// Calculate RSI
double Strategy::calculateRSI(const std::vector<double>& prices, int period) {
    if (prices.size() < period) return 0.0;

    double gain = 0.0, loss = 0.0;
    for (size_t i = 1; i < period; ++i) {
        double change = prices[i] - prices[i - 1];
        if (change > 0) {
            gain += change;
        } else {
            loss -= change;
        }
    }

    gain /= period;
    loss /= period;

    if (loss == 0) return 100.0;

    double rs = gain / loss;
    return 100.0 - (100.0 / (1.0 + rs));
}

// Calculate Bollinger Bands
std::tuple<double, double, double> Strategy::calculateBollingerBands(const std::vector<double>& prices, int period, double numStdDev) {
    if (prices.size() < period) return {0.0, 0.0, 0.0};

    double sum = std::accumulate(prices.end() - period, prices.end(), 0.0);
    double mean = sum / period;

    double sq_sum = std::inner_product(prices.end() - period, prices.end(), prices.end() - period, 0.0);
    double stdev = std::sqrt(sq_sum / period - mean * mean);

    double upperBand = mean + numStdDev * stdev;
    double lowerBand = mean - numStdDev * stdev;

    return {lowerBand, mean, upperBand};
}