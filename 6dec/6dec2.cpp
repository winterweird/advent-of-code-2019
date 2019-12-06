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

string common_ancestor(const string& a, const string& b) {
    auto da = depth(0, a);
    auto db = depth(0, b);
    auto maxnode = da < db ? b : a;
    auto othernode = da < db ? a : b;
    for (long long i = min(da,db); i < max(da,db); i++) {
        maxnode = parent[maxnode];
    }
    while (maxnode != othernode) {
        maxnode = parent[maxnode];
        othernode = parent[othernode];
    }
    return maxnode;
}

int main() {
    string l;
    while(getline(cin, l)) {
        int x = l.find(")");
        auto a = l.substr(0, x);
        auto b = l.substr(x+1);
        parent[b] = a;
    }

    auto ca = common_ancestor("YOU", "SAN");
    cout << ca << endl;
    cout << depth(0, "YOU") + depth(0, "SAN") - 2*depth(0, ca) - 2 << endl;
}
