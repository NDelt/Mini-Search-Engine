#include "tokenizer.hpp"

std::vector<std::string> Tokenizer::tokenize(std::string& query) {
    int spaceBegin  = 0;
    int spaceIdx    = 0;
    int queryLength = query.length();
    
    bool spacing = false;
    
    // 공백이 여러 개일 경우, 한 개의 공백만 남기고 모두 제거한다.
    for (int queryIdx = 0; queryIdx < queryLength; ++queryIdx) {
        const char c = query.at(queryIdx);
        
        if (c == ' ') {
            if (spacing) {
                continue;
            }
            
            spacing    = true;
            spaceBegin = queryIdx;
            spaceIdx   = queryIdx;
            
        } else {
            if (!spacing) {
                continue;
            }
            
            // ex)
            // [a b       c d e ...]
            //  0 1 2 3 4 5 6 7 ...
            // spaceBegin의 값: 2
            // 마지막 spaceIdx의 값: 5
            // 공백의 개수: offset = spaceIdx - spaceBegin = 3
            // 삭제해야 할 공백의 개수: offset - 1 = 2
            // 삭제 후 돌아갈 queryIdx의 위치: spaceIdx - offset = 2
            int offset = spaceIdx - spaceBegin;
            
            if (offset >= 2) {
                query.erase(spaceBegin, offset - 1);
                queryIdx = spaceIdx - offset;
            }
            
            spacing = false;
        }
        
        if (spacing) {
            ++spaceIdx;
        }
    }
    
    std::vector<std::string> internal = splitString(query);
    
    return internal;
}

std::vector<std::string> Tokenizer::splitString(std::string& str) {
    std::vector<std::string> internal;
    
    std::stringstream streamFrom(str); // 문자열 str을 기반으로 문자열 스트림을 생성한다.
    std::string       pushTo;
    
    // streamFrom 스트림으로부터 줄 단위(개행 문자 기준)로 문자열을 읽어들이면서, 공백 문자(' ')를 구분자로 하여 구분자 사이사이의 단어들을 pushTo 문자열에 저장한다.
    // 그리고 pushTo 문자열에 저장된 단어를 internal 벡터의 뒤쪽부터 추가한다.
    while (std::getline(streamFrom, pushTo, ' ')) {
        internal.push_back(pushTo);
    }
    
    return internal;
}
