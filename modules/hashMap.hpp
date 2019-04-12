#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#define HONOR_OFFSET 5
#define DEFAULT_SIZE 100000

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class HashSlot {
public:
    HashSlot() = delete;
    
    HashSlot(const std::string& pKey, const int pValue) : key(pKey), value(pValue) {};
    
    std::string getKey() const;
    
    int getValue() const;
    
    ~HashSlot() = default;

private:
    std::string key;
    
    int value;
};

class HashMap {
public:
    HashMap() : matrix(DEFAULT_SIZE), currentRowCount(0), currentSlotCount(0) {};
    
    void add(const std::string& key, const int value);
    
    std::vector<int> getValues(const std::string& key);
    
    void remove(const std::string& key, const int value);
    
    int getCurrentRowCount() const;
    
    ~HashMap() = default;

protected:
    int hashFunction(const std::string& key, const int totalRowCount);
    
    int stringToInt(const std::string& key) const;

private:
    std::vector<std::vector<HashSlot>> matrix; // 2차원 해시 테이블
    
    int currentRowCount;
    int currentSlotCount;
};

#endif
