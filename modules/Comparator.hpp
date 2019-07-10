#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

class Comparator {
public:
    friend class TableSearcher;
    
    Comparator() = default;
    
    ~Comparator() = default;
    
    static bool sortByFreq(const Comparator& a, const Comparator& b);

private:
    int count = 0;
    
    int index = 0;
    
    int value = 0;
};

#endif
