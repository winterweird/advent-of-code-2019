#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

map<pair<long long, long long>, long long> value_a;
map<pair<long long, long long>, long long> value_b;

long long sign(long long arg) {
    return arg < 0 ? -1 : arg > 0 ? 1 : 0;
}

struct point {
    long long x, y;
    point() {} // empty constructor
    point(long long x, long long y): x(x), y(y) {}
    pair<long long, long long> to_pair() const {
        return { x, y };
    }

    long long manhattan() const {
        return abs(x) + abs(y);
    }

    bool operator<(const point& other) const {
         return value_a[to_pair()] + value_b[to_pair()] < value_a[other.to_pair()] + value_b[other.to_pair()];
    }
    bool operator==(const point& other) const {
        return to_pair() == other.to_pair();
    }
};

struct line {
    point start, end;
    line(point a, point b): start(a), end(b) {}
    line() {} // empty constructor

    long long length() const {
        return abs(start.x - end.x) + abs(start.y - end.y);
    }

    long long dx() const {
        return sign(end.x-start.x);
    }
    long long dy() const {
        return sign(end.y-start.y);
    }

    // everything except starting point
    vector<point> to_points() const {
        vector<point> ret;
        long long x = start.x;
        long long y = start.y;
        for (int i = 1; i <= length(); i++) {
            ret.push_back({ x + i*dx(), y + i*dy() });
        }
        return ret;
    }
};

struct path {
    vector<line> lines;
    path(const vector<point>& points) {
        lines.resize(points.size()-1);
        for (int i = 0; i+1 < points.size(); i++) {
            lines[i] = { points[i], points[i+1] };
        }
    }
    vector<point> to_points() const {
        vector<point> ret;
        for (auto& l: lines) {
            auto ps = l.to_points();
            ret.insert(ret.end(), ps.begin(), ps.end());
        }
        return ret;
    }
};

void parse_line(vector<point>& points, const string& s) {
    char dir;
    char separator;
    long long steps;
    stringstream ss(s);

    points.push_back({ 0,0 });
    while (ss >> dir) {
        if (dir != 'R' && dir != 'L' && dir != 'U' && dir != 'D') {
            return;
        }

        auto last_point = points.back();

        ss >> steps;
        ss >> separator;
        long long dx = dir == 'R' ? steps : dir == 'L' ? -steps : 0;
        long long dy = dir == 'D' ? steps : dir == 'U' ? -steps : 0;
        points.push_back({  last_point.x + dx, last_point.y + dy  });
    }
}


// puts intersection point in ref
// return true if intersects
bool intersects(point& ref, const line& a, const line& b) {
    // assume lines are never parallel and overlapping
    if (a.start.x == a.end.x && b.start.x == b.end.x || a.start.y == a.end.y && b.start.y == b.end.y) {
        return false;
    }
    auto horizontal = a.start.x == a.end.x ? b : a;
    auto vertical = a.start.y == a.end.y ? b : a;
    if (horizontal.start.x < vertical.start.x && horizontal.end.x < vertical.end.x || horizontal.start.x > vertical.start.x && horizontal.end.x > vertical.end.x) return false;
    if (horizontal.start.y < vertical.start.y && horizontal.end.y < vertical.end.y || horizontal.start.y > vertical.start.y && horizontal.end.y > vertical.end.y) return false;
    ref.x = vertical.start.x;
    ref.y = horizontal.start.y;
    return true;
}

int main() {
    vector<point> points_a;
    vector<point> points_b;
    string l;

    getline(cin, l);
    parse_line(points_a, l);

    getline(cin, l);
    parse_line(points_b, l);
    cout << "HI" << endl;

    vector<point> intersections;

    cout << points_a.size() << endl;
    cout << points_b.size() << endl;
    path a(points_a);
    path b(points_b);
    vector<point> a_points = a.to_points();
    vector<point> b_points = b.to_points();
    cout << a_points.size() << endl;
    cout << b_points.size() << endl;

    for (auto& l1: a.lines) {
        for (auto& l2: b.lines) {
            point p;

            if (intersects(p, l1, l2)) {
                intersections.push_back(p);
                auto x = p.to_pair();

                if (value_a.find(x) == value_a.end()) {
                    auto it = find(a_points.begin(), a_points.end(), p);
                    value_a[x] = distance(a_points.begin(), it);
                }
                if (value_b.find(x) == value_b.end()) {
                    auto it = find(b_points.begin(), b_points.end(), p);
                    value_b[x] = distance(b_points.begin(), it);
                }

                cout << "Sum steps: " << value_a[x] + value_b[x] << endl;
                cout << endl;
            }
        }
    }

    sort(intersections.begin(), intersections.end());

    auto closest = intersections[0];
    cout << closest.x << " " << closest.y << endl;
    cout << value_a[closest.to_pair()] + value_b[closest.to_pair()] + 2 << endl;
}
