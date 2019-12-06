#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

map<string, string> parent;

long long depth(long long depthsofar, const string& k) {
    if (k.size() == 0) return depthsofar;
    return depth(depthsofar+1, parent[k]);
}

string common_ancestor(long long d1, long long d2, const string& a, const string& b) {
    if (a == b) return a;
    if (d1 > d2) return common_ancestor(d1-1, d2, parent[a], b);
    if (d2 > d1) return common_ancestor(d1, d2-1, a, parent[b]);
    return common_ancestor(d1-1,d2-1, parent[a], parent[b]);
}

int main() {
    string l;
    while(getline(cin, l)) {
        int x = l.find(")");
        auto a = l.substr(0, x);
        auto b = l.substr(x+1);
        parent[b] = a;
    }

    auto d1 = depth(0, "YOU");
    auto d2 = depth(0, "SAN");
    auto ca = common_ancestor(d1,d2,"YOU", "SAN");
    auto d3 = depth(0, ca);
    cout << ca << endl;
    cout << d1 + d2 - 2*d3 - 2 << endl;
}
