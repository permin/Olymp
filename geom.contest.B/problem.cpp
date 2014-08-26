#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <bitset>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {o << "[";O__(o, v);o << "]";return o;}

template <>
ostream& operator << (ostream& o, const vector<double>& v) {o << "["; for (size_t i = 0; i < v.size(); ++i) {
if (i) printf(", "); printf("%0.18lf", v[i]);};o << "]";return o;}

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

double sqr(double x) {
    return x * x;
}

double len(double x, double y) {
    return sqrt(sqr(x)+sqr(y));
}

struct Circle {
    double x, y, r;
};

double norm(double a) {
    while (a >= 2 * PI) {
        a -= 2 * PI;
    }
    while (a < 0) {
        a += 2 * PI;
    }
    return a;
}

double tangentDist(const Circle& c) {
    return sqrt(sqr(len(c.x, c.y)) - sqr(c.r));
}

pdd getAngle(const Circle& c) {
    double delta = atan2(c.r, tangentDist(c));
    double center = atan2(c.y, c.x);
    return pdd(norm(center - delta), norm(center + delta));
}

double distToClosetsPoint(const Circle& c) {
    return len(c.x, c.y) - c.r;
}

bool operator<(const Circle& first, const Circle& second) {
    return tangentDist(first) < tangentDist(second);
}

int main() {
    freopen("forest.in", "r", stdin);
    freopen("forest.out", "w", stdout);
    while (true) {
        int n;
        cin >> n;
        if (!n)
            break;
        std::vector<Circle> cs(n);
        for (int i = 0; i < n; ++i) {
            cin >> cs[i].x >> cs[i].y >> cs[i].r;
        }
        sort(all(cs));
        std::vector<double> angles;
        angles.push_back(0);
        angles.push_back(PI+PI);
        std::vector<pdd> range;
        for (size_t i = 0; i < cs.size(); ++i) {
            range.push_back(getAngle(cs[i]));
            angles.push_back(range.back().first);
            angles.push_back(range.back().second);
        }
        std::sort(all(angles));
        angles.erase(unique(all(angles)), angles.end());
        /*{
            const double EPS = 1e-9;
            vector<double> newAngles(1, 0.0);
            for (size_t i = 1; i < angles.size(); ++i) {
                if (angles[i] < newAngles.back() + EPS)
                    continue;
                angles.push_back(angles[i]);
            }
            angles = newAngles;
        }*/
        std::vector<size_t> num(angles.size());
        double res = 0.0;
        for (size_t i = 0; i < range.size(); ++i) {
            size_t x = std::distance(angles.begin(), std::lower_bound(all(angles), range[i].first));
            size_t y = std::distance(angles.begin(), std::lower_bound(all(angles), range[i].second));
            while (x != y) {
                if (num[x] == 0 && x != angles.size() - 1 && fabs(angles[x + 1] - angles[x]) > EPS) {
                    //debug(i);
                    res = max(res, distToClosetsPoint(cs[i]));
                }
                ++num[x];
                x += 1;
                if (x == angles.size()) {
                    x = 0;
                }
            }
        }
        printf("%0.3lf\n", res);
    }
    return 0;
}
