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
    
    // 중복 ID 값이 우선하도록 2차 정렬
    if (isThereDuplicate) {
        temporalSort(this->searchedDocs);
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
 * 출처: https://www.geeksforgeeks.org/sort-elements-by-frequency/
 */
void TableSearcher::temporalSort(std::vector<int>& array) {
    int size = (int)array.size();
    
    // Comparator 객체로 이루어진 vector를 생성한다.
    std::vector<Comparator> compArr((unsigned long)size);
    
    for (int i = 0; i < size; ++i) {
        compArr[i].index = i;        // Comparator 객체의 index 값을 i로 초기화
        compArr[i].count = 0;        // Comparator 객체의 count 값을 0으로 초기화
        compArr[i].value = array[i]; // Comparator 객체의 value 값을 인자로 주어진 array 배열의 i번 인덱스의 원소로 초기화
    }
    
    compArr[0].count = 1; // 첫 번째 원소의 count 값을 1로 설정
    
    for (int i = 1; i < size; ++i) {
        if (compArr[i].value == compArr[i - 1].value) { /* 현재 원소의 value 값이 이전 원소의 value 값과 동일할 경우 */
            /********************************************************************************************************
             '이전 원소의 count 값 + 현재 원소의 count 값 + 1'을 현재 원소의 count 값으로 지정한다.
             vector 생성 시 모든 원소의 count 값은 0으로 초기화되었기 때문에 1을 더한다.
             ********************************************************************************************************/
            compArr[i].count = compArr[i - 1].count + compArr[i].count + 1;
            
            /********************************************************************************************************
             중복된 원소를 구분하기 위해, 이전 원소의 count 값을 -1로 변경한다.
             ********************************************************************************************************/
            compArr[i - 1].count = -1;
            
            /********************************************************************************************************
             이전 원소의 index 값을 현재 원소의 index 값으로 변경한다.
             그 다음 원소가 똑같은 value 값을 가졌을 경우 현재 원소의 index 값이 다음 원소의 index 값으로 지정된다.
             이렇게 하여 첫 번째로 중복된 원소의 index 값이 마지막으로 중복된 원소의 index로 복사되도록 만든다.
             ********************************************************************************************************/
            compArr[i].index = compArr[i - 1].index;
            
        } else { /* 현재 원소의 value 값이 이전 원소의 value 값과 다를 경우 */
            compArr[i].count = 1; // 중복되지 않는 최초의 원소이기 때문에 count 값을 1로 지정한다.
        }
    }
    
    /************************************************************************************************************************
     sortByFreq()를 std::sort()의 정렬 기준 함수로 전달하여 정렬을 수행한다.
     sortByFreq() 함수는 count 값이 작은 원소를 앞쪽으로 정렬한다. 따라서 count 값이 -1인 원소들은 전부 vector의 앞쪽에 오게 된다.
     std::sort()는 정렬 기준을 설정하는 콜백 함수가 true를 반환하면 첫 번째 매개변수가 두 번째 매개변수보다 앞서도록 정렬한다.
     ************************************************************************************************************************/
    std::sort(compArr.begin(), compArr.end(), Comparator::sortByFreq);
    
    /************************************************************************************************************************
     이 temporalSort() 함수의 목적은 count의 값이 큰 순으로, count가 같을 경우 index 값이 작은 순으로 array 배열을 정렬하는 것이다.
     하지만 위의 연산을 수행하고 나면 compArr 배열은 count 값이 작은 순으로, count가 같을 경우 index 값이 큰 순으로 정렬되기 때문에
     출력 시에는 compArr 배열의 마지막 원소부터 역순으로 순회해야 한다.
     ************************************************************************************************************************/
    for (int i = size - 1, index = 0; i >= 0; --i) {
        if (compArr[i].count != -1) { /* count 값이 -1인 중복 원소가 아닐 경우 */
            for (int j = 0; j < compArr[i].count; ++j) {
                array[index++] = compArr[i].value;
                // 예를 들어 compArr[1]의 count 값이 3이라면, compArr[1]의 value 값을 array 배열에 연속으로 세 번 저장한다.
            }
        }
    }
}
