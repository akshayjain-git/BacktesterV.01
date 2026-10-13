#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

#include "OHLCV.h"

std::vector<OHLCV> readCSV(const std::string& filename) {

    std::vector<OHLCV> data;

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file: " + filename);
    }

    std::string line;

    if (!std::getline(file, line)) {
        throw std::runtime_error("CSV file is empty: " + filename);
    }

    std::size_t lineNumber = 1;
    while (getline(file, line)) {
        ++lineNumber;
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string date, openStr, highStr, lowStr, closeStr;
        std::string adjustedCloseStr, volumeStr;

        // yfinance order: Date, Open, High, Low, Close, Adj Close, Volume, ...
        if (!std::getline(ss, date, ',') || !std::getline(ss, openStr, ',') ||
            !std::getline(ss, highStr, ',') || !std::getline(ss, lowStr, ',') ||
            !std::getline(ss, closeStr, ',') || !std::getline(ss, adjustedCloseStr, ',') ||
            !std::getline(ss, volumeStr, ',')) {
            throw std::runtime_error("Malformed CSV row at line " + std::to_string(lineNumber));
        }

        try {
            data.push_back({date, std::stod(openStr), std::stod(highStr), std::stod(lowStr),
                            std::stod(closeStr), std::stod(adjustedCloseStr),
                            std::stoll(volumeStr)});
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid numeric value at CSV line " + std::to_string(lineNumber));
        }
    }

    return data;
}
