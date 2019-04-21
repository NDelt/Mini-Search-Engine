#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

class Comparator {
public:
    Comparator() = default;
    
    ~Comparator() = default;
    
    static bool sortByFreq(const Comparator& a, const Comparator& b);
    
    void setCount(int count);
    
    void setIndex(int index);
    
    void setValue(int value);
    
    int getCount();
    
    int getIndex();
    
    int getValue();

private:
    int count = 0;
    
    int index = 0;
    
    int value = 0;
};

#endif
