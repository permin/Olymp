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
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {o << "[";O__(o, v);o << "]";return o;}

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long double, long double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const long double PI = 3.1415926535897932384626433832795;
const long double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

long double sqr(long double x) {
    return x * x;
}

#define CLOSE(x,y) assert(fabs(x-(y))<1e-4);

vector<pdd> intersect(long double A, long double B, long double C, long double R) {
    long double d = sqrt(A*A + B*B);
    A /= d;
    B /= d;
    C /= d;
    CLOSE(sqr(A)+sqr(B), 1.0);

    if (C > R)
        return {};
    long double len = sqrt(R*R-C*C);
    vector<pdd> res;
    res.emplace_back(-A*C + len * (-B), -B * C + len * A);
    res.emplace_back(-A*C - len * (-B), -B * C - len * A);
    for (int i = 0; i < res.size(); ++i) {
        CLOSE(sqr(R), sqr(res[i].first) + sqr((res[i].second)));
    }
    return res;
}

vector<pdd> intersect(long double x0, long double y0, long double r0, long double x1, long double y1, long double r1) {
    long double C = sqr(x1) - sqr(x0) + sqr(y1) - sqr(y0) + sqr(r0) - sqr(r1);
    long double A = -2.0 * (x1 - x0);
    long double B = -2.0 * (y1 - y0);
    auto t = intersect(A, B, + A * x0 + B * y0 + C, r0);
    for (auto& x: t) {
        x.first += x0;
        x.second += y0;

        CLOSE(sqr(x1-x.first)+sqr(y1-x.second), sqr(r1));
        CLOSE(sqr(x0-x.first)+sqr(y0-x.second), sqr(r0));
    }
    return t;
}

int main() {

    long double x,y;
    vector<pdd> p;
    while(cin >> x >> y) {
        p.emplace_back(x, y);
    }
    vector<pdd> c(p);
    for (int i = 0; i < p.size(); ++i)
        for (int j = i + 1; j < p.size(); ++j) {
            vector<pdd> r = intersect(p[i].first, p[i].second, 2.5, p[j].first, p[j].second, 2.5);
            for (auto q: r)
                c.push_back(q);
        }
    int res = 0;
    for (auto cc: c) {
        int cur = 0;
        for (auto pp: p) {
            if (sqr(pp.first - cc.first) + sqr(pp.second - cc.second) <= sqr(2.5) )
                ++cur;
        }
        res = max(res, cur);
    }
    cout << res << "\n";

    return 0;
}

