CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(Mini-Search-Engine-Cpp)

IF (MSVC)
    SET(CMAKE_CXX_FLAGS "/W4 /WX /Za /permissive- /EHsc")
ELSE ()
    SET(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
ENDIF ()

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_VERBOSE_MAKEFILE TRUE)
SET(TARGET mini-search-engine)
SET(SOURCES src/main.cpp
    src/TableIndexer.cpp src/CSVParser.cpp src/QueryParser.cpp src/TableSearcher.cpp
    modules/Tokenizer.cpp modules/Normalizer.cpp modules/HashMap.cpp)
SET(OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/output)

ADD_EXECUTABLE(${TARGET} ${SOURCES})

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
