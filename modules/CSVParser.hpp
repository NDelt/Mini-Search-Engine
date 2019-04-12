#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class CSVParser {
public:
    CSVParser() = delete;
    
    static std::vector<std::vector<std::string>> parse(const std::string& filePath);
    
    ~CSVParser() = default;
};

#endif
