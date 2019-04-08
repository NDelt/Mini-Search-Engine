#include <iostream>
#include <fstream>
#include <vector>

#include "../modules/hashMap.hpp"

void HashMapTest() {
    HashMap hm;
    
    hm.Add("January", 1);
    hm.Add("February", 2);
    hm.Add("February", 3);
    hm.Add("March", 4);
    hm.Add("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5);
    hm.Add("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 6);
    hm.Add("April", 7);
    hm.Add("April", 8);
    hm.Add("April", 9);
    hm.Add("May", 10);
    
    std::vector<int> ret1 = hm.Get("February");
    std::vector<int> ret2 = hm.Get("April");
    std::vector<int> ret3 = hm.Get("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    for (int i : ret1) {
        std::cout << i << " ";
    }
    
    std::cout << "\n";
    
    for (int i : ret2) {
        std::cout << i << " ";
    }
    
    std::cout << "\n";
    
    for (int i : ret3) {
        std::cout << i << " ";
    }
    
    hm.Remove("February", 3);
    
    std::vector<int> ret4 = hm.Get("February");
    std::cout << "\n";
    
    for (int i : ret4) {
        std::cout << i << " ";
    }
}
