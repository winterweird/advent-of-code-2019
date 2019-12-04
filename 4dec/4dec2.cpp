#include <iostream>

using namespace std;

// encapsulates the constraint
bool matches(long long a) {
    long long c = a;
    long long digit;
    bool conseqSeen = false;
    long long twodigit, threedigit;
    while (c > 0) {
        digit = c%10;
        twodigit = c%100;
        threedigit = c%1000;

        if (twodigit / 10 > digit) { return false; }
        if (digit*11 == twodigit) {
            if (digit*111 == threedigit) {
                // this group is invalid; keep removing it until it's gone
                while (c % 100 == twodigit) {
                    c /= 10;
                }
                continue;
            }
            else {
                conseqSeen = true;
            }
        }
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
