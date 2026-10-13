# BacktesterV.01

A C++17 command-line backtester for a 20/50-day simple moving average crossover strategy. The initial dataset is daily TCS (TCS.NS) price history in `TCS_5Y.csv`.

## Build and run

Requirements: a C++17 compiler and CMake 3.16 or newer.

```sh
cmake -S . -B build
cmake --build build
./build/backtester
```

CMake copies `TCS_5Y.csv` into the build directory. Run the executable from that directory (as above) so it can find the CSV. The strategy parameters and initial capital are currently defined in `src/main.cpp`.

## Refresh the sample data

The included script downloads five years of daily history for TCS.NS using `yfinance` and writes `TCS_5Y.csv` in the current directory:

```sh
python -m pip install yfinance
python download_data.py
```

After updating the CSV, reconfigure the build so CMake copies the new file, then rebuild and run:

```sh
cmake -S . -B build
cmake --build build
./build/backtester
```

## Current assumptions and limitations

This version is a simple educational baseline. It invests all available cash on a buy, sells the entire position on a sell, permits fractional shares, and does not model commissions, taxes, slippage, cash interest, or partial fills. It uses adjusted close for both signal calculation and trade fills. The report contains only a small set of summary metrics, and there is no command-line configuration, multi-asset portfolio, or strategy selection yet.

These assumptions can make simulated results differ substantially from real trading. Treat the output as an experiment with historical data, not as a prediction or investment recommendation.

## Project structure

- `src/main.cpp` — fixed strategy parameters and program flow
- `src/csvreader.cpp` — CSV input
- `src/indicators.cpp` — simple moving average calculation
- `src/signals.cpp` — crossover signal generation
- `src/backtest.cpp` — portfolio simulation and drawdown calculation
- `src/report.cpp` — console performance summary
- `download_data.py` — sample market data downloader
- `TCS_5Y.csv` — bundled historical sample data

## Possible next steps

A natural progression for the project is to make the current experiment configurable, then broaden what can be studied:

1. Move symbol, date range, capital, and indicator windows into runtime configuration.
2. Add more indicators and make strategies independently selectable.
3. Expand reporting with benchmark comparisons, equity curves, and additional risk and return metrics.
4. Model transaction costs and execution choices, and make the assumptions visible in each report.
5. Support multiple symbols and portfolio-level allocation and risk controls.
6. Add repeatable tests and sample datasets as the engine grows.
