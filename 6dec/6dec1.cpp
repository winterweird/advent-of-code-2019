#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

map<string, string> parent;

long long depth(long long depthsofar, const string& k) {
    if (k.size() == 0) {
        return depthsofar;
    }
    return depth(depthsofar+1, parent[k]);
}

int main() {
    string l;
    while(getline(cin, l)) {
        int x = l.find(")");
        auto a = l.substr(0, x);
        auto b = l.substr(x+1);
        parent[b] = a;
    }
    long long checksum = 0;

    for (auto const& p: parent) {
        checksum += depth(0, p.second);
    }
    cout << checksum << endl;
}
