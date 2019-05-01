#include "Comparator.hpp"

// 두 배열 원소의 등장 빈도가 다를 경우 빈도수로 비교를 수행한다. a의 count 값이 더 작으면 true가 반환되어 a가 앞쪽으로 정렬된다.
// 등장 빈도가 동일할 경우 인덱스 값으로 비교를 수행하며 이 때는 a의 인덱스 값이 더 크면 true가 반환되어 a가 앞쪽으로 정렬된다.
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
