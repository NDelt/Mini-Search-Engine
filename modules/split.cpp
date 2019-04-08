#include "split.hpp"

std::vector<std::string> split_string(std::string& str) {
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
