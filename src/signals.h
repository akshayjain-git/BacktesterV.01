#pragma once

#include <vector>

enum class Signal { None, Buy, Sell };

std::vector<Signal> detectCrossovers(const std::vector<double>& fastSMA,
                                     const std::vector<double>& slowSMA);
