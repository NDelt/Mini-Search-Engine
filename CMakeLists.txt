# <------------ Based on Linux distributions --------------->
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(WebIndexer_CppModule)

SET(CMAKE_CXX_COMPILER "c++")
SET(CMAKE_CXX_FLAGS "-std=c++17 -m64 -pedantic -Wall -Wextra -Werror")
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE TRUE)

SET(SOURCES src/main.cpp
    src/TableIndexer.cpp src/CSVParser.cpp src/QueryParser.cpp src/TableSearcher.cpp
    modules/Comparator.cpp modules/Tokenizer.cpp modules/Normalizer.cpp modules/HashMap.cpp)

ADD_EXECUTABLE(main ${SOURCES})
