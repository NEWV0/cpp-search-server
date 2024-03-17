#include <iostream>
#include <string>

using namespace std;

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cout << boolalpha;
        cout << file << "("s << line << "): "s << func << ": "s;
        cout << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cout << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cout << " Hint: "s << hint;
        }
        cout << endl;
        abort();
    }
}

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

int Sum(int a, int b) {
    // Ошибка допущена намеренно, чтобы продемонстрировать вывод информации об ошибке
    return a + b + 1;
}

int main() {
    string hello = "hello"s;
    ASSERT_EQUAL(hello.length(), 5);

    // Эта проверка не пройдёт
    ASSERT_EQUAL_HINT(Sum(2, 2), 4, "Sum() must be correct"s);
}