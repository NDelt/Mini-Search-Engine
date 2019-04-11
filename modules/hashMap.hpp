#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#define HONOR_OFFSET 5
#define DEFAULT_SIZE 15

#include <iostream>
#include <limits>
#include <vector>
#include <string>

class HashSlot {
public:
    HashSlot(const std::string& pKey, const int pValue) : key(pKey), value(pValue) {};
    
    std::string getKey() const;
    
    int getValue() const;

private:
    std::string key;
    
    int value;
};

class HashMap {
public:
    HashMap() : matrix(DEFAULT_SIZE), currentRowCount(0), currentSlotCount(0) {};
    
    void add(const std::string& key, const int value);
    
    std::vector<int> getValues(const std::string& key);
    
    int getRowSize(const int value);
    
    void remove(const std::string& key, const int value);
    
    int getCurrentRowCount();

protected:
    std::vector<std::vector<HashSlot>> matrix; // 2차원 해시 테이블
    
    int hashFunction(const std::string& key, const int totalRowCount);
    
    int stringToInt(const std::string& key) const;

private:
    int currentRowCount;
    int currentSlotCount;
};

#endif
