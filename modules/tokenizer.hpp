#ifndef STRINGSPLIT_HPP
#define STRINGSPLIT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "split.hpp"

class Tokenizer {
public:
    Tokenizer() = delete;
    
    static std::vector<std::string> tokenize(std::string& query);
    
    ~Tokenizer() = default;
};

#endif
