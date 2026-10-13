cmake_minimum_required(VERSION 3.16)

project(BacktesterV01 LANGUAGES CXX)

add_executable(backtester
    src/main.cpp
    src/csvreader.cpp
    src/indicators.cpp
    src/signals.cpp
    src/backtest.cpp
    src/report.cpp
)

target_compile_features(backtester PRIVATE cxx_std_17)

# The program opens this file by name from its working directory.
configure_file(TCS_5Y.csv TCS_5Y.csv COPYONLY)
