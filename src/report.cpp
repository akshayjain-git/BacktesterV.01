#include "report.h"

#include <iomanip>
#include <iostream>

void printReport(const std::string& title, const std::vector<OHLCV>& data,
                 const BacktestResult& result, double initialCapital) {
    std::cout << std::fixed << std::setprecision(2)
              << title << "\n"
              << "Data rows: " << data.size() << "\n";
    if (!data.empty()) {
        std::cout << "Period: " << data.front().date << " to " << data.back().date << "\n";
    }
    std::cout << "Price series: Adjusted Close\n"
              << "Execution: Next day's adjusted close\n"
              << "Initial capital: " << initialCapital << "\n"
              << "Total return: " << result.totalReturnPercent << "%\n"
              << "Completed trades: " << result.completedTrades << "\n"
              << "Maximum drawdown: " << result.maxDrawdownPercent << "%\n"
              << "Position at end: " << (result.positionOpenAtEnd ? "Open (marked to market)" : "Closed")
              << "\n";
}
