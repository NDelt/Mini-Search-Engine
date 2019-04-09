#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "queryParser.hpp"
#include "../modules/hashMap.hpp"

class Searcher {
public:
    void Search(std::string& searchQuery, HashMap& hashMap);

private:
    std::vector<int> searchedDocs;
};

#endif
