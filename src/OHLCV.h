#pragma once
#include <string>

struct OHLCV {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double adjustedClose;
    long long volume;
};
