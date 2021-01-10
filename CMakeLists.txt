cmake_minimum_required(VERSION 3.16)
project(Ex5)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ex5 MainTrain.cpp anomaly_detection_util.cpp
        SimpleAnomalyDetector.cpp timeseries.cpp HybridAnomalyDetector.cpp minCircle.cpp CLI.cpp
        ShareKnowledge.cpp CommandUpload.cpp CommandAlgoSettings.cpp CommandDetectAnomalies.cpp
        CommandAnalyzeResults.cpp CommandDisplayResults.cpp)