#include <iostream>

using namespace std;

// Calculate the fuel required for the mass
long long fuel(long long mass) {
    if (mass <= 0)
        return 0;
    auto f = mass/3-2;
    if (f <= 0) return 0;
    return f + fuel(f);
}

int main() {
    long long n;
    long long sum = 0;
    while (cin >> n) {
        sum += fuel(n);
    }
    cout << sum << endl;
}
