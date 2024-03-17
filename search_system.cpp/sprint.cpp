#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include <map>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}



template <typename Type>
class Stack {
public:
    void Push(const Type& element) {
        elements_.push_back(element);
    }
    void Pop() {
        elements_.pop_back();
    }
    const Type& Peek() const {
        return elements_.back();
    }
    Type& Peek() {
        return elements_.back();
    }
    void Print() const {
        PrintRange(elements_.begin(), elements_.end());
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.empty();
    }

private:
    vector<Type> elements_;
};

template <typename Type>
class SortedSack {
public:
    void Push(const Type& element) {
        auto it = lower_bound(elements_.begin(), elements_.end(), element, greater<Type>());
        elements_.insert(it, element);
    }

    void Pop() {
        if (!elements_.empty()) {
            elements_.pop_back(); 
        }
    }

    const Type& Peek() const {
        return elements_.back(); 
    }

    Type& Peek() {
        return elements_.back(); 
    }

    void Print() const {
        PrintRange(elements_.begin(), elements_.end()); 
    }

    uint64_t Size() const {
        return elements_.size();
    }

    bool IsEmpty() const {
        return elements_.empty(); 
    }

private:
    vector<Type> elements_;
};

int main() {
    SortedSack<int> sack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего класса
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);

    // заполняем класс и проверяем, что сортировка сохраняется после каждой вставки
    for (int i = 0; i < 5; ++i) {
        cout << "input element = "s << values[i] << endl;
        sack.Push(values[i]);
        sack.Print();
    }
} 