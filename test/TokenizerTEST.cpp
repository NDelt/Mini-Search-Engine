#include <iostream>
#include <fstream>

#include "../modules/Tokenizer.hpp"

class tokenizerTest {
public:
    void sampleTokenizing() {
        std::ifstream reader("../resources/sample_text.txt");
        std::string   convertedStr;
        
        while (std::getline(reader, convertedStr)) {
            std::cout << "-------------------- Original paragraph --------------------\n";
            std::cout << convertedStr << "\n";
            std::cout << "------------------------------------------------------------\n";
            
            // 토큰 분리 메소드 호출
            for (const std::string& tempStr : Tokenizer::tokenize(convertedStr)) {
                testVtr.push_back(tempStr);
            }
        }
    }
    
    std::vector<std::string> getTestVtr() {
        return testVtr;
    }

private:
    std::vector<std::string> testVtr;
};
