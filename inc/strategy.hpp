#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>
#include <vector>
#include <numeric>

/**
 * @class Strategy
 * @brief Provides various technical analysis functions for stock prices, such as moving averages, RSI, and Bollinger Bands.
 */
class Strategy
{
public:
    /// Number of periods for short period moving average
    const static int shortPeriod = 5;
    
    /// Number of periods for long period moving average
    const static int longPeriod = 20;
    
    /**
     * @brief Calculates the short-period simple moving average (SMA).
     * @param prices Vector of historical stock prices.
     * @return The short-period SMA.
     */
    static double calculateShortPeriodMovingAverage(const std::vector<double>& prices);

    /**
     * @brief Calculates the long-period simple moving average (SMA).
     * @param prices Vector of historical stock prices.
     * @return The long-period SMA.
     */
    static double calculateLongPeriodMovingAverage(const std::vector<double>& prices);

    /**
     * @brief Calculates the Relative Strength Index (RSI) over a specified period.
     * @param prices Vector of historical stock prices.
     * @param period Number of periods to use for RSI calculation (default is 14).
     * @return The RSI value.
     */
    static double calculateRSI(const std::vector<double>& prices, int period = 14);

    /**
     * @brief Calculates the Bollinger Bands for a given set of prices.
     * @param prices Vector of historical stock prices.
     * @param period Number of periods to use for the moving average (default is 20).
     * @param numStdDev Number of standard deviations to calculate the upper and lower bands (default is 2.0).
     * @return A tuple containing the lower band, middle band (SMA), and upper band.
     */
    static std::tuple<double, double, double> calculateBollingerBands(const std::vector<double>& prices, int period = 20, double numStdDev = 2.0);
};

#endif // STRATEGY_HPP
