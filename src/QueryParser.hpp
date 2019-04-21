#ifndef QUERYPARSER_HPP
#define QUERYPARSER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "../modules/Normalizer.hpp"
#include "../modules/Tokenizer.hpp"

class QueryParser {
public:
    QueryParser() = delete;
    
    ~QueryParser() = default;
    
    static std::vector<std::string> parse(std::string& query);
};

#endif
