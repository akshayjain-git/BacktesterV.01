#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "OHLCV.h"
#include "backtest.h"
#include "indicators.h"
#include "report.h"
#include "signals.h"

std::vector<OHLCV> readCSV(const std::string& filename);

namespace {
constexpr std::size_t FastWindow = 20;
constexpr std::size_t SlowWindow = 50;
constexpr double InitialCapital = 100000.0;
}

int main() {
    try {
        const auto data = readCSV("TCS_5Y.csv");
        if (data.empty()) {
            std::cerr << "No price data found in TCS_5Y.csv\n";
            return 1;
        }

        std::vector<double> adjustedCloses;
        adjustedCloses.reserve(data.size());
        for (const auto& candle : data) {
            if (candle.adjustedClose <= 0.0) {
                throw std::runtime_error("Adjusted close must be positive");
            }
            adjustedCloses.push_back(candle.adjustedClose);
        }

        const auto fastSMA = calculateSMA(adjustedCloses, FastWindow);
        const auto slowSMA = calculateSMA(adjustedCloses, SlowWindow);
        const auto signals = detectCrossovers(fastSMA, slowSMA);
        const auto result = simulateTrades(data, signals, InitialCapital);
        printReport("TCS 20/50 SMA crossover backtest", data, result, InitialCapital);
    } catch (const std::exception& error) {
        std::cerr << "Backtest error: " << error.what() << "\n";
        return 1;
    }
    return 0;
}
