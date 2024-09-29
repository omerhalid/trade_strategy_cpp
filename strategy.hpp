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
};