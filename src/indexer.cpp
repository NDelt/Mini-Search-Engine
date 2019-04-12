#include "indexer.hpp"

/**
 * 역색인 테이블 생성기
 * 1) CSV 파싱
 * 2) 'BASIC QUALIFICATIONS' 컬럼에 대해 토큰 단위로 문자열 파싱
 * 3) 문자열 파싱 후 반환되는 vector를 순회하며 (토큰, ID) 형식으로 해시 테이블에 데이터 추가
 */

void Indexer::createIndex(const std::string& filePath, HashMap& hashMap) {
    clock_t start, end;
    double  result;
    
    std::cout << std::fixed;
    std::cout.precision(4);
    
    std::cout << ">>>>> Parsing CSV file....\n";
    
    start = clock();
    std::cout << "* File path : " << "\"" << filePath << "\"\n";
    std::vector<std::vector<std::string>> matrix = parseCSV(filePath);
    end = clock();
    
    result = (double)(end - start);
    
    std::cout << ">>>>> CSV parsing complete. [" << result / CLOCKS_PER_SEC << "s]\n\n";
    
    int csvParsingCount = 1;
    
    // 사용하는 CSV 파일 컬럼: ID(0), TITLE(1), BASIC QUALIFICATIONS(5)
    // 토큰 분석 대상 컬럼: BASIC QUALIFICATIONS(5)
    for (const std::vector<std::string>& row : matrix) {
        std::cout << ">>>>> (" << csvParsingCount << ") Parsing words...\n";
        start = clock();
        
        this->id            = std::atoi(row[0].c_str());
        this->title         = row[1];
        this->qualif = row[5];
        
        std::cout << "* ID : " << this->id << "\n";
        std::cout << "* Job Title : " << this->title << "\n";
        std::cout << "* Qualifications : " << this->qualif << "\n\n";
        
        std::vector<std::string> retVec = QueryParser::parse(this->qualif);
        
        int interCount = 1;
        
        for (const std::string& str : retVec) {
            if (str.empty()) {
                std::cout << "(empty) / ";
            } else if (str.size() == 1) {
                std::cout << "(1 letter) / ";
            } else if (str == "an" || str == "the") {
                std::cout << "(stopword) / ";
            } else {
                std::cout << str << " / ";
                hashMap.add(str, this->id);
            }
            
            ++interCount;
        }
        
        std::cout << "\n";
        
        end    = clock();
        result = (double)(end - start);
        
        std::cout << ">>>>> (" << csvParsingCount << ") CSV parsing complete. [" << result / CLOCKS_PER_SEC << "s]\n\n";
        
        ++csvParsingCount;
    }
    
    std::cout << ">>>>> Word parsing complete.\n";
    std::cout << ">>>>> Inverted index table is created : " << hashMap.getCurrentRowCount() << " rows.\n\n";
}
