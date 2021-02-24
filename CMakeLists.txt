CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(Mini-Search-Engine-Cpp)

SET(CMAKE_CXX_STANDARD 17)

IF (MSVC)
    SET(CMAKE_CXX_FLAGS "/W4 /WX /Za /permissive- /EHsc")
ELSE ()
    SET(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
ENDIF ()

SET(CMAKE_VERBOSE_MAKEFILE TRUE)

SET(SOURCES src/main.cpp
    src/TableIndexer.cpp src/CSVParser.cpp src/QueryParser.cpp src/TableSearcher.cpp
    modules/Tokenizer.cpp modules/Normalizer.cpp modules/HashMap.cpp)

ADD_EXECUTABLE(main ${SOURCES})
