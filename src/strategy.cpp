#include "../inc/strategy.hpp"

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