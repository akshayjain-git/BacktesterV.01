#include "backtest.h"

#include <algorithm>
#include <stdexcept>

BacktestResult simulateTrades(const std::vector<OHLCV>& data,
                              const std::vector<Signal>& signals,
                              double initialCapital) {
    if (data.size() != signals.size()) {
        throw std::invalid_argument("Price data and signals must have the same length");
    }
    if (initialCapital <= 0.0) throw std::invalid_argument("Initial capital must be positive");

    BacktestResult result;
    double cash = initialCapital;
    double shares = 0.0;
    double peakEquity = initialCapital;

    // A signal at close i is filled at the adjusted close on day i+1.
    for (std::size_t i = 0; i + 1 < data.size(); ++i) {
        const double fillPrice = data[i + 1].adjustedClose;
        if (fillPrice <= 0.0) throw std::runtime_error("Adjusted close must be positive");

        if (signals[i] == Signal::Buy && shares == 0.0) {
            shares = cash / fillPrice; // Fully invested, fractional shares, no costs.
            cash = 0.0;
        } else if (signals[i] == Signal::Sell && shares > 0.0) {
            cash = shares * fillPrice;
            shares = 0.0;
            ++result.completedTrades;
        }

        const double equity = cash + shares * fillPrice;
        peakEquity = std::max(peakEquity, equity);
        result.maxDrawdownPercent = std::max(
            result.maxDrawdownPercent, (peakEquity - equity) / peakEquity * 100.0);
    }

    if (!data.empty()) {
        const double finalPrice = data.back().adjustedClose;
        if (finalPrice <= 0.0) throw std::runtime_error("Adjusted close must be positive");
        const double finalEquity = cash + shares * finalPrice;
        peakEquity = std::max(peakEquity, finalEquity);
        result.maxDrawdownPercent = std::max(
            result.maxDrawdownPercent, (peakEquity - finalEquity) / peakEquity * 100.0);
        result.totalReturnPercent = (finalEquity / initialCapital - 1.0) * 100.0;
        result.positionOpenAtEnd = shares > 0.0;
    }
    return result;
}
