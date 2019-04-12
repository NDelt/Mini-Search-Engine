#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class CSVParser {
public:
    CSVParser() = delete;
    
    static std::vector<std::vector<std::string>> parse(const std::string& filePath);
    
    ~CSVParser() = default;
};

#endif
