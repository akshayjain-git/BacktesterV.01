# BacktesterV.01

A C++17 command-line backtester for a 20/50-day simple moving average crossover strategy. The initial dataset is daily TCS (TCS.NS) price history in `TCS_5Y.csv`.

## Build and run

```sh
cmake -S . -B build
cmake --build build
./build/backtester
```

The executable reads `TCS_5Y.csv` from its working directory. CMake copies the CSV into the build directory during configuration.

## Refresh the dataset

`download_data.py` downloads five years of daily history using `yfinance`:

```sh
python -m pip install yfinance
python download_data.py
```
