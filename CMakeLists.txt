cmake_minimum_required(VERSION 3.16)
project(Ex5)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -std=c++11")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(Ex5 MainTrain.cpp anomaly_detection_util.cpp
        SimpleAnomalyDetector.cpp timeseries.cpp HybridAnomalyDetector.cpp minCircle.cpp CLI.cpp
        Server.cpp)