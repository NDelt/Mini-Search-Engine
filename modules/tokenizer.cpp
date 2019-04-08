#include <sstream>

#include "tokenizer.hpp"

std::vector<std::string> Tokenizer(std::string& query) {
    int spaceBegin = 0;
    int spaceIdx   = 0;
    
    bool spacing = false;
    
    // 공백이 여러 개일 경우, 한 개의 공백만 남기고 모두 제거한다.
    for (int queryIdx = 0; queryIdx < static_cast<int>(query.length()); ++queryIdx) {
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
    
    std::vector<std::string> internal = split_string(query);
    
    return internal;
}
