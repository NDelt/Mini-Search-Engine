#include "Comparator.hpp"

// 두 배열 원소의 등장 빈도가 다르면 빈도수로 비교한다.
// a의 count 값이 더 작으면 true가 반환되는데, std::sort()는 정렬 기준 함수가 true를 반환하면 첫 번째 매개변수(a)가 두 번째 매개변수보다 앞서도록 정렬한다.
// 등장 빈도가 동일할 경우 인덱스 값으로 비교를 수행하며 이 때는 a의 인덱스 값이 더 클 때 true가 반환되어 a가 앞쪽으로 정렬된다.
bool Comparator::sortByFreq(const Comparator& a, const Comparator& b) {
    if (a.count != b.count) {
        return (a.count < b.count);
    } else {
        return (a.index > b.index);
    }
}

void Comparator::setCount(int count) {
    this->count = count;
}

void Comparator::setIndex(int index) {
    this->index = index;
}

void Comparator::setValue(int value) {
    this->value = value;
}

int Comparator::getCount() {
    return this->count;
}

int Comparator::getIndex() {
    return this->index;
}

int Comparator::getValue() {
    return this->value;
}
