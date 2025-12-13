cmake_minimum_required(VERSION 4.0)
project(hi)

set(CMAKE_CXX_STANDARD 20)

add_executable(SentimentAnalysisEngine src/main.cpp
        src/Functions.cpp
        include/Functions.h
        include/Utils.h
        include/Models.h)
