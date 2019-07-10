#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <cstdlib>
#include <ctime>

#include "CSVParser.hpp"
#include "QueryParser.hpp"

#include "../modules/HashMap.hpp"

class TableIndexer {
public:
    TableIndexer() : id(0), title(""), qualif("") {};
    
    ~TableIndexer() = default;
    
    void createIndex(const std::string& filePath, HashMap& hashMap);

private:
    int id;
    
    std::string title;
    std::string qualif;
};

#endif
