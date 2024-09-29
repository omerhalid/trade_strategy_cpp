#include "strategy.hpp"

double Strategy::calculateShortPeriodMovingAverage(const std::vector<double>& prices) {
    if (prices.size() < shortPeriod) return 0.0;
    double sum = std::accumulate(prices.end() - shortPeriod, prices.end(), 0.0);
    return sum / shortPeriod;
}

double Strategy::calculateLongPeriodMovingAverage(const std::vector<double>& prices) {
    if (prices.size() < longPeriod) return 0.0;
    double sum = std::accumulate(prices.end() - longPeriod, prices.end(), 0.0);
    return sum / longPeriod;
}