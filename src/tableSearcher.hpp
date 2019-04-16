#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

// #include <sw/redis++/redis++.h>

#include "queryParser.hpp"

#include "../modules/hashMap.hpp"

class TableSearcher {
public:
    TableSearcher() = default;
    
    ~TableSearcher() = default;
    
    void search(std::string& searchQuery, HashMap& hashMap);

private:
    std::vector<int> searchedDocs;
};

#endif
