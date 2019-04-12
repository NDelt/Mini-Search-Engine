#include "queryParser.hpp"

std::vector<std::string> QueryParser::parse(std::string& query) {
    std::vector<std::string> retVec;
    
    // HTML 태그와 각종 특수문자를 제거, 대문자를 소문자로 변환
    std::string retStr = Normalizer::normalize(query);
    
    // 띄어쓰기를 기준삼아 쿼리 문자열을 토큰으로 분리하고, 문자열 벡터에 저장
    retVec = Tokenizer::tokenize(query);
    
    return retVec;
}
