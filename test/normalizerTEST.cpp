#include <iostream>
#include <fstream>

#include "../modules/normalizer.hpp"

class normalizerTest {
public:
    void sampleNormalizing() {
        std::ifstream reader("../resources/sample_text.txt");
        std::string   convertedStr;
        
        while (std::getline(reader, convertedStr)) {
            std::cout << "-------------------- Original paragraph --------------------\n";
            std::cout << convertedStr << "\n";
            std::cout << "------------------------------------------------------------\n";
            
            // 노멀라이징 메소드 호출
            testVtr.push_back(Normalizer::normalize(convertedStr));
        }
    }
    
    std::vector<std::string> getTestVtr() {
        return testVtr;
    }

private:
    std::vector<std::string> testVtr;
};
