#include <iostream>
#include <fstream>
#include <vector>

#include "../modules/hashMap.hpp"

void hashMapTest() {
    HashMap hm;
    
    hm.add("January", 1);
    hm.add("February", 2);
    hm.add("February", 3);
    hm.add("March", 4);
    hm.add("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5);
    hm.add("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 6);
    hm.add("April", 7);
    hm.add("April", 8);
    hm.add("April", 9);
    hm.add("May", 10);
    
    std::vector<int> ret1 = hm.getValues("February");
    std::vector<int> ret2 = hm.getValues("April");
    std::vector<int> ret3 = hm.getValues("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
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
    
    hm.remove("February", 3);
    
    std::vector<int> ret4 = hm.getValues("February");
    std::cout << "\n";
    
    for (int i : ret4) {
        std::cout << i << " ";
    }
}
