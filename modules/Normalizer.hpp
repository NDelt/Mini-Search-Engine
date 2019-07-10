#ifndef NORMALIZER_HPP
#define NORMALIZER_HPP

#include <iostream>
#include <string>
#include <vector>

class Normalizer {
public:
    Normalizer() = delete;
    
    ~Normalizer() = default;
    
    static std::string normalize(std::string& query);
};

#endif
