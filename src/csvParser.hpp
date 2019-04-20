#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

class CSVParser {
public:
    CSVParser() = delete;
    
    ~CSVParser() = default;
    
    static std::vector<std::vector<std::string>> parse(const std::string& filePath);
};

#endif
