#pragma once

#include <string>
#include <vector>

#include "OHLCV.h"
#include "backtest.h"

void printReport(const std::string& title, const std::vector<OHLCV>& data,
                 const BacktestResult& result, double initialCapital);
