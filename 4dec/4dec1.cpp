#include <iostream>

using namespace std;

// encapsulates the constraint
bool matches(long long a) {
    long long c = a;
    long long digit, prev = 10;
    bool conseqSeen = false;
    while (c > 0) {
        digit = c%10;
        if (digit > prev) {
            return false;
        }
        if (digit == prev) { conseqSeen = true; }
        prev = digit;
        c /= 10;
    }
    return conseqSeen;
}

int main() {
    long long a, b;
    char separator;
    cin >> a >> separator >> b;
    cout << a << " " << b << endl;
    long long count = 0;
    for (long long i = a; i <= b; i++) {
        if (matches(i)) { count++; }
    }
    cout << count << endl;
}
