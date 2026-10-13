#pragma once

#include <cstddef>
#include <vector>

#include "OHLCV.h"
#include "signals.h"

struct BacktestResult {
    double totalReturnPercent = 0.0;
    double maxDrawdownPercent = 0.0;
    std::size_t completedTrades = 0;
    bool positionOpenAtEnd = false;
};

BacktestResult simulateTrades(const std::vector<OHLCV>& data,
                              const std::vector<Signal>& signals,
                              double initialCapital);
