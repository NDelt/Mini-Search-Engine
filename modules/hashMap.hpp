#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#define HONOR_OFFSET 5
#define DEFAULT_SIZE 100000

#include <iostream>
#include <list>
#include <limits>
#include <vector>
#include <string>

class HashSlot {
public:
    HashSlot(const std::string& pKey, const int pValue) : key(pKey), value(pValue) {};
    
    std::string GetKey() const;
    
    int GetValue() const;

private:
    std::string key;
    
    int value;
};

class HashMap {
public:
    HashMap() : matrix(DEFAULT_SIZE), currentRowCount(0) {};
    
    void Add(const std::string& key, const int value);
    
    std::vector<int> Get(const std::string& key);
    
    void Remove(const std::string& key, const int value);
    
    int GetCurrentRowCount();

protected:
    int HashFunction(const std::string& key, const int totalRowCount);
    
    int StringToInt(const std::string& key) const;

private:
    std::vector<std::list<HashSlot>> matrix; // 2차원 해시 테이블
    
    int currentRowCount;
};

#endif
