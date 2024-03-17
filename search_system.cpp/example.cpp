#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stack>
#include <utility>
#include <limits>

using namespace std;

template <typename Type>
class StackMin {
public:
  void Push(const Type& element) {
    if (elements_.empty()) {
        elements_.push(make_pair(element, element));
    } else {
        Type min_value = min(element, elements_.top().second);
        elements_.push(make_pair(element, min_value));
    }
}

  void Pop() {
    if (!elements_.empty()) {
        elements_.pop();
    }
}

    const Type& Peek() const {
        return elements_.top().first;
    }

    Type& Peek() {
        return elements_.top().first;
    }

    void Print() const {
        stack<pair<Type, Type>> temp = elements_;
        while (!temp.empty()) {
            cout << temp.top().first << " ";
            temp.pop();
        }
        cout << endl;
    }

    uint64_t Size() const {
        return elements_.size();
    }

    bool IsEmpty() const {
        return elements_.empty();
    }

    const Type& PeekMin() const {
        return elements_.top().second;
    }

    Type& PeekMin() {
        return elements_.top().second;
    }

private:
    stack<pair<Type, Type>> elements_;
};

int main() {
    StackMin<int> stack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего стека
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);
    // заполняем стек
    for (int i = 0; i < 5; ++i) {
        stack.Push(values[i]);
    }
    // печатаем стек и его минимум, постепенно убирая из стека элементы
    while (!stack.IsEmpty()) {
        stack.Print();
        cout << "Минимум = "s << stack.PeekMin() << endl;
        stack.Pop();
    }
}