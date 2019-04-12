#include "normalizer.hpp"

std::string Normalizer::normalize(std::string& query) {
    std::string retStr;
    
    int removeBegin = 0;
    int removeIdx   = 0;
    int queryLength = query.length();
    
    bool removing = false;
    
    // 쿼리 문자열을 순회하며 HTML 태그와 특수문자 제거
    for (int queryIdx = 0; queryIdx < queryLength; ++queryIdx) {
        char c = query.at(queryIdx);
        
        // 대문자를 소문자로 변환
        if (c >= 65 && c <= 90) {
            c += 32;
            std::string temp(1, c);
            query.replace(queryIdx, 1, temp);
            continue;
        }
        
        switch (c) {
            case '<':
                removing    = true;
                removeBegin = queryIdx;
                removeIdx   = queryIdx;
                break;
            case '>':
                if (!removing) {
                    break;
                }
                // ex)
                // [a d < p r e > w o r ...]
                //  0 1 2 3 4 5 6 7 8 9 ...
                // removeBegin의 값: 2
                // 마지막 removeIdx의 값: 6
                // 삭제해야 할 인덱스의 개수: removeIdx - removeBegin + 1 = 5
                // queryIdx의 복귀 위치: removeIdx - (removeIdx - removeBegin + 1) = 6 - 5 = 1
                query.erase(removeBegin, removeIdx - removeBegin + 1);
                queryIdx    = removeIdx - (removeIdx - removeBegin + 1); // queryIdx의 위치를 삭제한 단어(<...>)의 앞쪽 인덱스로 수정
                removeIdx   = 0;
                removeBegin = 0;
                removing    = false;
                break;
            case '.':
            case ',':
            case '\'':
            case '"':
            case '-':
            case ':':
            case ';':
            case '(':
            case ')':
            case '/':
            case '?':
            case '#':
                query.erase(queryIdx, 1); // queryIdx 인덱스부터 1개의 원소를 제거
                query.insert(queryIdx, " "); // 제거한 위치에 공백 삽입
                queryIdx -= 1;
                break;
            default:
                break;
        }
        
        if (removing) {
            ++removeIdx;
        }
    }
    
    retStr = query;
    
    return retStr;
}
