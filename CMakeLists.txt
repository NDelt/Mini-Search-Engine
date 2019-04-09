# <------------ Based on Linux distributions --------------->
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(WebIndexer_CppModule)

SET(CMAKE_CXX_COMPILER "c++")
SET(CMAKE_CXX_FLAGS "-std=c++17 -m64 -pedantic -Wall -Wextra -Werror")
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE TRUE)

SET(SOURCES src/main.cpp src/indexer.cpp src/queryParser.cpp src/searcher.cpp
    modules/tokenizer.cpp modules/normalizer.cpp modules/hashMap.cpp modules/split.cpp modules/CSVParser.cpp)

ADD_EXECUTABLE(main ${SOURCES})

# <------------ mysql-cpp-connector dependency (compatible with MariaDB) --------------->
# TARGET_LINK_LIBRARIES(main mysqlcppconn)

# <------------ hiredis dependency --------------->
# FIND_PATH(HIREDIS_HEADER hiredis)
# TARGET_INCLUDE_DIRECTORIES(main PUBLIC ${HIREDIS_HEADER})
#
# FIND_LIBRARY(HIREDIS_LIB hiredis)
# TARGET_LINK_LIBRARIES(main ${HIREDIS_LIB})

# <------------ redis-plus-plus dependency -------------->
# FIND_PATH(REDIS_PLUS_PLUS_HEADER sw)      # NOTE: this should be *sw* NOT *redis++*
# TARGET_INCLUDE_DIRECTORIES(main PUBLIC ${REDIS_PLUS_PLUS_HEADER})
#
# FIND_LIBRARY(REDIS_PLUS_PLUS_LIB redis++)
# TARGET_LINK_LIBRARIES(main ${REDIS_PLUS_PLUS_LIB})
