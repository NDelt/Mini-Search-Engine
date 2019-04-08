#ifndef QUERYPARSER_HPP
#define QUERYPARSER_HPP

#include <iostream>
#include <vector>
#include <string>

#include "../modules/normalizer.hpp"
#include "../modules/tokenizer.hpp"

/*
 * 검색어 문자열을 여러 개의 토큰으로 분리하는 파서
 * Parse() 메소드가 반환하는 벡터의 0번 원소는 주어진 쿼리가 속한 DB 레코드의 ID 값
 */

class QueryParser {
public:
    static std::vector<std::string> Parse(std::string& query);
};

#endif
