#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "QueryParser.hpp"

#include "../modules/Comparator.hpp"
#include "../modules/HashMap.hpp"

class TableSearcher {
public:
    TableSearcher() = default;
    
    ~TableSearcher() = default;
    
    void search(std::string& searchQuery, HashMap& hashMap);

protected:
    std::vector<int> findDuplicate(const std::vector<int>& array);
    
    void temporalSort(std::vector<int>& array);

private:
    std::vector<int> searchedDocs;
    
    bool isThereDuplicate = false;
};

#endif
