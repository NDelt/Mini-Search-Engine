#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>

#include "QueryParser.hpp"

#include "../modules/HashMap.hpp"

class TableSearcher {
public:
    TableSearcher() = default;
    
    ~TableSearcher() = default;
    
    void search(std::string& searchQuery, HashMap& hashMap);

protected:
    std::vector<int> findDuplicate(const std::vector<int>& array);
    
    // std::sort()에 인자로 전달될 멤버 함수는 static으로 선언한다.
    static bool comparator(const std::pair<int, int>& a, const std::pair<int, int>& b);
    
    void sortByFreq(std::vector<int>& array);

private:
    std::vector<int> searchedDocs;
    
    bool isThereDuplicate = false;
    
    // 예전에는 static 멤버 변수를 헤더 파일에 선언하면 소스 파일에서 링킹 에러가 발생했지만(별도로 정의되지 않았기 때문에),
    // C++17부터는 inline 키워드를 이용하여 헤더 파일 선언이 가능하게 되었다.
    inline static std::unordered_map<int, int> firstFreq;
};

#endif
