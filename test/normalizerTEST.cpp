#include <iostream>
#include <fstream>

#include "../modules/normalizer.hpp"

class NormalizerTest {
public:
    void SampleNormalizing() {
        std::ifstream reader("../resources/sample_text.txt");
        std::string   convertedStr;
        
        while (std::getline(reader, convertedStr)) {
            std::cout << "-------------------- Original paragraph --------------------\n";
            std::cout << convertedStr << "\n";
            std::cout << "------------------------------------------------------------\n";
            
            // 노멀라이징 메소드 호출
            testVtr.push_back(Normalizer(convertedStr));
        }
    }
    
    std::vector<std::string> GetTestVtr() {
        return testVtr;
    }

private:
    std::vector<std::string> testVtr;
    
};
