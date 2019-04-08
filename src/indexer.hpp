#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <cstdlib>
#include <ctime>

#include "queryParser.hpp"

#include "../modules/CSVParser.hpp"
#include "../modules/hashMap.hpp"

class Indexer {
public:
    Indexer() : id(0), title(""), qualification("") {};
    
    void CreateIndex(const std::string& filePath, HashMap& hashMap);

private:
    int id;
    
    std::string title;
    std::string qualification;
};

#endif
