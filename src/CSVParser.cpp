#include "csvParser.hpp"

/**
 * CSV 파서
 * #) 파일의 한 라인당 콤마(,)를 기준으로 문자열을 읽어 vector에 추가
 * #) 큰 따옴표로 둘러쌓인 컬럼의 경우, 콤마의 개수와 관계없이 하나의 문자열로 인식
 * #) 컬럼 내부의 강조 문자열(이중 큰 따옴표, ""..."") 인식 가능
 */

std::vector<std::vector<std::string>> CSVParser::parse(const std::string& filePath) {
    std::fstream reader;
    reader.open(filePath);
    
    std::vector<std::vector<std::string>> matrix; // 2차원 vector
    
    if (reader.fail()) {
        std::cout << "Error - '" << filePath << "' does not exist!\n";
        std::_Exit(EXIT_FAILURE);
    }
    
    std::string line;
    
    // 한 줄 읽기
    while (std::getline(reader, line, '\n')) {
        std::vector<std::string> row;
        std::string              column;
        
        int startFieldIdx = 0;
        int endFieldIdx   = 0;
        int startQuoteIdx = 0;
        int endQuoteIdx   = 0;
        
        bool inColumn    = false;
        bool inQuotes    = false;
        bool twiceQuotes = false;
        
        // 한 줄에서 한 단어씩 읽기
        for (int queryIdx = 0; queryIdx < (int)line.size(); ++queryIdx) {
            const char c = line.at(queryIdx);
            
            switch (c) {
                case '"':
                    /* queryIdx에 +1을 하기 전 line.size()에 대한 경계값 검사 */
                    if (queryIdx + 1 < (int)line.size() && line.at(queryIdx + 1) == '"') {
                        twiceQuotes = true;
                        goto SKIPPED; // 따옴표가 연속으로 두 번 나타나는 경우, 컬럼 단위가 아니므로 스킵
                    }
                    if (!inQuotes) { // 여는 따옴표를 만났을 때
                        inQuotes      = true;
                        startQuoteIdx = queryIdx;
                        endQuoteIdx   = queryIdx;
                    } else { // 닫는 따옴표를 만났을 때
                        inQuotes = false;
                        // ex)
                        // [" S o f t w a r e " ...]
                        //  0 1 2 3 4 5 6 7 8 9 ...
                        // startQuoteIdx의 값: 0
                        // 마지막 endQuoteIdx의 값: 8
                        // 따옴표 내 문자 개수: endQuoteIdx - startQuoteIdx = 8
                        row.push_back(line.substr(startQuoteIdx + 1, endQuoteIdx - startQuoteIdx));
                    }
                    break;
                case ',':
                    if (inQuotes) {
                        goto SKIPPED; // 따옴표 안쪽일 경우 스킵
                    } else if (line.at(queryIdx - 1) == '"') {
                        break; // 닫는 따옴표 뒤에 구분자(,)가 나타나는 경우, 이미 문자열을 저장한 상황이므로 switch 블록 탈출
                    }
                    inColumn = false;
                    // ex)
                    // [S o f t w a r e , ...]
                    //  0 1 2 3 4 5 6 7 8 ...
                    // startFieldIdx의 값: 0
                    // 마지막 endFieldIdx의 값: 7
                    // 구분자 이전의 문자 개수: endFieldIdx - startFieldIdx + 1
                    row.push_back(line.substr(startFieldIdx, endFieldIdx - startFieldIdx + 1));
                    break;
                default:
                SKIPPED:
                    if (!inColumn && !inQuotes) { // 구분자 이후로 일반 문자를 처음 만났고, 따옴표 안쪽이 아닐 때
                        inColumn      = true;
                        startFieldIdx = queryIdx;
                        endFieldIdx   = queryIdx;
                    } else if (inQuotes) { // 구분자 이후로 일반 문자를 처음 만났고, 따옴표 안쪽일 때
                        if (twiceQuotes) { // 이중 따옴표를 만나서 스킵된 경우
                            twiceQuotes = false;
                            ++queryIdx;
                            endQuoteIdx += 2;
                        } else {
                            ++endQuoteIdx;
                        }
                    } else { // 구분자 이후로 일반 문자를 두 번 이상 만났고, 따옴표 안쪽이 아닐 때
                        ++endFieldIdx;
                    }
                    break;
            }
        }
        
        matrix.push_back(row);
    }
    
    reader.close();
    
    return matrix;
}
