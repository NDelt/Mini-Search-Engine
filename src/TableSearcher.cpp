#include "TableSearcher.hpp"

/**
 * 역색인 테이블 검색기
 * #) 인자로 주어진 검색어를 토큰 단위로 분리하고, 각각의 토큰에 대한 값 vector를 반환받아 오름차순으로 정렬한 뒤 출력한다.
 */

void TableSearcher::search(std::string& searchQuery, HashMap& hashMap) {
    std::vector<std::string> parsedString;
    std::vector<int>         taken;
    
    int wordCount = 0;
    
    clock_t start, end;
    double  result;
    
    std::cout << std::fixed;
    std::cout.precision(4);
    
    start = clock();
    
    if (searchQuery.length() == 1) {
        std::cout << "1-letter word could not be searched.\n";
        
        end    = clock();
        result = (double)(end - start);
        
        std::cout << ">>>>> " << result / CLOCKS_PER_SEC << "s\n\n";
        
        return;
    }
    
    parsedString = QueryParser::parse(searchQuery);
    
    for (const std::string& str : parsedString) {
        taken = hashMap.getValues(str);
        
        // 'searchedDocs' vector의 끝에 'taken' vector를 이어붙인다.
        this->searchedDocs.insert(this->searchedDocs.end(), taken.begin(), taken.end());
        
        if (!this->searchedDocs.empty()) {
            ++wordCount;
        }
    }
    
    // 오름차순으로 1차 정렬: 첫 번째 인자에 해당하는 원소부터 두 번째 인자에 해당하는 원소 이전까지를 정렬한다.
    std::sort(this->searchedDocs.begin(), this->searchedDocs.end());
    
    // 중복된 ID 값 탐색(검색어가 두 개 이상의 단어로 이루어졌을 경우 공통 ID 추출)
    std::vector<int> duplicate = findDuplicate(this->searchedDocs);
    
    // 중복 ID 값이 우선하도록 빈도수 기반으로 2차 정렬
    if (isThereDuplicate) {
        sortByFreq(this->searchedDocs);
    }
    
    // 중복 원소 제거
    this->searchedDocs.erase(std::unique(this->searchedDocs.begin(), this->searchedDocs.end()), this->searchedDocs.end());
    
    for (int i : this->searchedDocs) {
        std::cout << i << " ";
    }
    
    std::cout << "\n";
    
    this->searchedDocs.clear();
    isThereDuplicate = false;
    
    end    = clock();
    result = (double)(end - start);
    
    std::cout << ">>>>> " << result / CLOCKS_PER_SEC << "s\n\n";
}

std::vector<int> TableSearcher::findDuplicate(const std::vector<int>& array) {
    if (array.empty()) {
        return {};
    }
    
    int lastValue = array.at(array.size() - 1);
    
    std::vector<int> duplicate((unsigned long)lastValue + 1);
    
    // 예를 들어 array의 원소 2를 만났다면, duplicated의 2번 인덱스의 값을 1 증가시킨다.
    for (int val : array) {
        ++duplicate.at((unsigned long)val);
    }
    
    // 값이 2 이상인 원소가 하나라도 있다면 중복이 발생한 것이다.
    for (int idx = 0; idx < (int)duplicate.size(); ++idx) {
        if (duplicate.at((unsigned long)idx) != 1) {
            isThereDuplicate = true;
            break;
        }
    }
    
    return duplicate;
}

/*
 * 빈도수 기반 정렬 알고리즘(Sort elements by frequency)
 * 출처: https://www.geeksforgeeks.org/sort-elements-frequency-set-4-efficient-approach-using-hash/
 *
 * 1. 각 원소별 등장 횟수를 저장하는 테이블 m1과, 해당 원소가 첫 번째로 등장한 인덱스를 저장하는 테이블 m2를 생성한다.
 * 2. m1의 원소 쌍을 배열에 저장하고 정렬한다.
 * -- 등장 횟수에 따라 내림차순으로 정렬하고, 등장 횟수가 동일하면 m2에서 먼저 등장한 원소 쌍이 무엇인지 확인하여 그 원소가 앞서도록 정렬한다.
 * 3. 각 원소를 등장 횟수만큼 반복하며 다른 배열에 옮겨 담는다.
 */
void TableSearcher::sortByFreq(std::vector<int>& array) {
    std::unordered_map<int, int> totalFreq;
    firstFreq.clear();
    
    for (int i = 0; i < (int)array.size(); ++i) {
        // totalFreq에 array[i]라는 키가 없을 경우, 해당 키를 할당하고 0이 값으로 자동 지정된다. 그리고 ++에 의해 값이 1 증가한다.
        ++totalFreq[array[i]];
        
        if (firstFreq[array[i]] == 0) {
            firstFreq[array[i]] = i;
        }
    }
    
    std::vector<std::pair<int, int>> pairs;
    
    for (const auto& tp : totalFreq) {
        pairs.push_back(std::make_pair(tp.first, tp.second));
    }
    
    std::sort(pairs.begin(), pairs.end(), comparator);
    std::vector<std::pair<int, int>>::iterator vecIter = pairs.begin();
    
    array.clear();
    
    // std::pair<>형 원소를 가진 vector에 대해서는 Range-based for문을 사용할 수 없다.
    while (vecIter != pairs.end()) {
        for (int i = 0; i < vecIter->second; ++i) {
            array.push_back(vecIter->first);
        }
        
        ++vecIter;
    }
}

bool TableSearcher::comparator(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    // 등장 횟수가 같을 경우, 해당 값이 처음 등장한 인덱스가 앞설 때 먼저 배치되도록 정렬한다.
    if (a.second == b.second) {
        return firstFreq[a.first] < firstFreq[b.first];
    }
    
    // 등장 횟수가 다를 경우, 그 등장 횟수에 따라 내림차순 정렬한다.
    return a.second > b.second;
}
