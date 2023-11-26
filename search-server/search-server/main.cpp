#include <iostream>

using namespace std;

int main() {
    int x = 0;
    for (int i = 1; i <= 1000; ++i) {
        if (i % 10 == 3  (i / 10) % 10 == 3  i / 100 == 3) {
            ++x;
        }
    }
    cout << x << endl;
}