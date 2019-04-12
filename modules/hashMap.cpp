#include "hashMap.hpp"

/**
 * 해시 슬롯 클래스
 */

std::string HashSlot::getKey() const {
    return this->key;
}

int HashSlot::getValue() const {
    return this->value;
}

/**
 * 해시 테이블 클래스
 */

void HashMap::add(const std::string& key, const int value) {
    int rowIdx = hashFunction(key, this->matrix.size());
    
    if (rowIdx == -1) {
        return;
    }
    
    if (rowIdx < (int)this->matrix.size()) {
        std::vector<HashSlot>& colVtr = this->matrix.at(rowIdx);
        
        auto itr    = colVtr.begin();
        auto endItr = colVtr.end();
        
        while (itr != endItr) {
            if (!colVtr.empty() && (*itr).getKey() == key && (*itr).getValue() == value) {
                return; // rowIdx 인덱스에 위치한 vector에 인자로 전달된 키와 값을 가진 원소가 이미 존재한다면 슬롯을 추가하지 않는다.
            }
            
            ++itr;
        }
    }
    
    if (rowIdx >= (int)this->matrix.size()) {
        this->matrix.resize(this->matrix.size() + DEFAULT_SIZE); // 해시 테이블의 행 수는 기본값 100000(십만)부터 시작하여 초기 사이즈와 동일한 폭으로 늘어난다.
    }
    
    HashSlot slot(key, value);
    this->matrix.at(rowIdx).push_back(slot);
    
    ++(this->currentSlotCount);
    
    if (this->matrix.at(rowIdx).size() == 1) {
        ++(this->currentRowCount); // 특정 vector에 첫 번째 슬롯이 추가될 때 사용 중인 행 수를 1 증가시킨다.
    }
}

std::vector<int> HashMap::getValues(const std::string& key) {
    int matrixSize = this->matrix.size();
    int divider    = DEFAULT_SIZE;
    
    bool valueFound = false;
    
    std::vector<int> ret;
    
    while (divider <= matrixSize) {
        int rowIdx = hashFunction(key, divider);
        
        if (rowIdx == -1) {
            return ret;
        }
        
        std::vector<HashSlot>& colVtr = this->matrix.at(rowIdx); // colVtr이 matrix vector의 rowIdx 인덱스에 위치한 vector를 참조한다.
        
        auto itr    = colVtr.begin();
        auto endItr = colVtr.end();
        
        while (itr != endItr) {
            if ((*itr).getKey() == key) {
                valueFound = true;
                ret.push_back((*itr).getValue());
            }
            
            ++itr;
        }
        
        divider += DEFAULT_SIZE;
    }
    
    if (!valueFound) {
        std::cout << "No matching values for '" << key << "'";
    }
    
    return ret;
}

void HashMap::remove(const std::string& key, const int value) {
    int  divider    = DEFAULT_SIZE;
    bool valueFound = false;
    
    while (divider <= (int)this->matrix.size()) {
        int rowIdx = hashFunction(key, divider);
        
        if (rowIdx == -1) {
            std::cout << "'" << key << "' is cannot be parsed.\n";
            return;
        }
        
        std::vector<HashSlot>& colVtr = this->matrix.at(rowIdx);
        
        auto itr    = colVtr.begin();
        auto endItr = colVtr.end();
        
        while (itr != endItr) {
            if ((*itr).getKey() == key && (*itr).getValue() == value) {
                valueFound = true;
                colVtr.erase(itr); // itr이 가리키는 HashSlot 원소를 삭제한다.
                break;
            }
            
            ++itr;
        }
        
        --(this->currentSlotCount);
        
        if (colVtr.empty()) {
            --(this->currentRowCount);
        }
        
        divider += DEFAULT_SIZE;
    }
    
    if (!valueFound) {
        std::cout << "No matching values for '" << key << "'";
    }
}

int HashMap::getCurrentRowCount() const {
    return this->currentRowCount;
}

int HashMap::hashFunction(const std::string& key, const int totalRowCount) {
    int ret     = -1;
    int tempKey = 0;
    int offset  = 1;
    
    // 현재 사용 중인 vector의 개수가 100000의 배수라면 테이블의 모든 행이 가득 찬 것이므로, vector의 개수를 인덱스로 지정한다.(= 다음 100000개의 첫 번째 행)
    if (this->currentRowCount % DEFAULT_SIZE == 0) {
        ret = this->currentRowCount;
        return ret;
    }
    
    tempKey = stringToInt(key);
    
    if (tempKey < 0) {
        return ret;
    }
    
    // 해싱: 검색 키를 테이블의 행 수로 나눈 나머지가 해시 값이 된다.
    if (this->currentRowCount <= DEFAULT_SIZE) {
        ret = tempKey % DEFAULT_SIZE;
    } else {
        ret = tempKey % totalRowCount;
    }
    
    int initialRet = ret;
    
    while (true) {
        std::vector<HashSlot>& colVtr = this->matrix.at(ret);
        auto itr = colVtr.begin();
        
        // 해시 값에 해당하는 vector에 이미 원소가 저장되어 있고, 그 원소의 키가 인자로 주어진 키와 다를 경우 다시 해싱한다.
        if (!colVtr.empty() && (*itr).getKey() != key) {
            if (this->currentRowCount <= DEFAULT_SIZE) {
                ret = (tempKey + offset) % DEFAULT_SIZE;
            } else {
                ret = (tempKey + offset) % totalRowCount;
            }
            
            // 새로 계산한 해시 값이 초기 해시 값과 동일할 경우, 한 바퀴 순회가 끝날 동안 올바른 vector를 찾지 못한 것이므로 반복을 중단한다.
            if (ret == initialRet) {
                break;
            }
            
            ++offset;
            
        } else {
            break;
        }
    }
    
    return ret;
}

int HashMap::stringToInt(const std::string& key) const {
    int ret = 0;
    
    /*
     * ex) HONOR_OFFSET = x, KEY = 54321
     * f(x) = 5x^4 + 4x^3 + 3x^2 + 2x + 1
     *      = (5x^3 + 4x^2 + 3x + 2)x + 1
     *      = ((5x^2 + 4x + 3)x + 2)x + 1
     *      = (((5x + 4)x + 3)x + 2)x + 1
     *      = ...
     *      = (((ax + C)x + C)x + C)x + C
     *
     * --> 'ax + C'의 재귀
     */
    for (const char c : key) {
        if (ret >= std::numeric_limits<int>::max() / 2) {
            ret /= 2; // 변환된 정수가 int형 최댓값의 절반 이상이 되면 해당 값을 반으로 나눈 후 즉시 반환한다.
            return ret;
        }
        
        ret = (ret * HONOR_OFFSET) + (int)c; // Honor's method를 이용하여 문자열을 정수로 변환한다.
    }
    
    return ret;
}
