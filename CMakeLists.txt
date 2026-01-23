cmake_minimum_required(VERSION 3.20)
project(backtesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(backtesting
        src/main.cpp
        src/Engine.cpp
        src/Indicator.cpp
        src/MovingAverageCrossover.cpp
        src/MeanReversion.cpp
)

target_include_directories(backtesting
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
