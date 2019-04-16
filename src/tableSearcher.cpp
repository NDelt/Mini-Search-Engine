#include "tableSearcher.hpp"

/**
 * 역색인 테이블 검색기
 * #) 인자로 주어진 검색어를 토큰 단위로 분리하고, 각각의 토큰에 대한 값 vector를 반환받아 오름차순으로 정렬한 뒤 출력한다.
 */

void TableSearcher::search(std::string& searchQuery, HashMap& hashMap) {
    std::vector<std::string> parsedString;
    std::vector<int>         taken;
    
    clock_t start, end;
    double  result;
    
    std::cout << std::fixed;
    std::cout.precision(4);
    
    start = clock();
    
    parsedString = QueryParser::parse(searchQuery);
    
    for (const std::string& str : parsedString) {
        taken = hashMap.getValues(str);
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
    
    std::cout << ">>>>> " << result / CLOCKS_PER_SEC << "s\n\n";
}
