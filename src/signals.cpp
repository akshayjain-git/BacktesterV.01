#include "signals.h"

#include <stdexcept>

std::vector<Signal> detectCrossovers(const std::vector<double>& fastSMA,
                                     const std::vector<double>& slowSMA) {
    if (fastSMA.size() != slowSMA.size()) {
        throw std::invalid_argument("SMA series must have the same length");
    }

    std::vector<Signal> signals(fastSMA.size(), Signal::None);
    for (std::size_t i = 1; i < fastSMA.size(); ++i) {
        // Ignore indices before the slow SMA is available (represented by zero).
        if (slowSMA[i - 1] == 0.0 || slowSMA[i] == 0.0) continue;
        if (fastSMA[i - 1] <= slowSMA[i - 1] && fastSMA[i] > slowSMA[i]) {
            signals[i] = Signal::Buy;
        } else if (fastSMA[i - 1] >= slowSMA[i - 1] && fastSMA[i] < slowSMA[i]) {
            signals[i] = Signal::Sell;
        }
    }
    return signals;
}
