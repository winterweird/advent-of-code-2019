#include <iostream>

using namespace std;

int main() {
    unsigned long long n;
    unsigned long long sum = 0;
    while (cin >> n) {
        sum += n / 3 - 2;
    }
    cout << sum << endl;
}
