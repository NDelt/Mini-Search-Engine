#ifndef STRINGSPLIT_HPP
#define STRINGSPLIT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Tokenizer {
public:
    Tokenizer() = delete;
    
    ~Tokenizer() = default;
    
    static std::vector<std::string> tokenize(std::string& query);
    
    static std::vector<std::string> splitString(std::string& str);
};

#endif
