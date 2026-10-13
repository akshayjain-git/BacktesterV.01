#include "indicators.h"

#include <stdexcept>

std::vector<double> calculateSMA(const std::vector<double>& prices, std::size_t window) {
    if (window == 0) throw std::invalid_argument("SMA window must be greater than zero");

    std::vector<double> sma(prices.size(), 0.0);
    double sum = 0.0;
    for (std::size_t i = 0; i < prices.size(); ++i) {
        sum += prices[i];
        if (i >= window) sum -= prices[i - window];
        if (i + 1 >= window) sma[i] = sum / static_cast<double>(window);
    }
    return sma;
}
