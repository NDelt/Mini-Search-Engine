#include "searcher.hpp"

void Searcher::Search(std::string& searchQuery, HashMap& hashMap) {
    std::vector<std::string> parsedString;
    
    clock_t start, end;
    double  result;
    
    start = clock();
    
    parsedString = QueryParser::Parse(searchQuery);
    
    for (const std::string& str : parsedString) {
        std::vector<int> taken = hashMap.Get(str);
        this->searchedDocs.insert(this->searchedDocs.end(), taken.begin(), taken.end());
    }
    
    // 중복 원소 제거
    std::sort(this->searchedDocs.begin(), this->searchedDocs.end());
    this->searchedDocs.erase(std::unique(this->searchedDocs.begin(), this->searchedDocs.end()), this->searchedDocs.end());
    
    for (int i : this->searchedDocs) {
        std::cout << i << " ";
    }
    
    std::cout << "\n";
    this->searchedDocs.clear();
    
    end    = clock();
    result = (double)(end - start);
    
    printf(">>>>> (%0.4lfs)\n", result / CLOCKS_PER_SEC);
}
