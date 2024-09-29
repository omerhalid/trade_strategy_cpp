#include <iostream>
#include <vector>
#include <numeric>

class Strategy
{
public:
    const static int shortPeriod = 5;
    const static int longPeriod = 20;
    
    // calculate moving average
    static double calculateShortPeriodMovingAverage(const std::vector<double>& prices);
    static double calculateLongPeriodMovingAverage(const std::vector<double>& prices);

    // calculate RSI
    static double calculateRSI(const std::vector<double>& prices, int period = 14);

    // calculate Bollinger Bands
    static std::tuple<double, double, double> calculateBollingerBands(const std::vector<double>& prices, int period = 20, double numStdDev = 2.0);
};