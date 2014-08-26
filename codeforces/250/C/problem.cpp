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
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

ll sign(ll x) {
    if (x == 0)
        return 0;
    return x > 0? +1:-1;
}

ll det2(int a, int b, int c, int d) {
    return 1LL * a * d - 1LL * b * c;
}

ll area(int x0, int y0, int x1, int y1, int x2, int y2) {
    return 1LL * x0 * det2(y1, 1, y2, 1) -
           1LL * y0 * det2(x1, 1, x2, 1) +
           1LL * det2(x1, y1, x2, y2);
}

bool intersect(int x, int y, int a, int b) {
    if (x > y)
        swap(x,y);
    if (a > b)
        swap(a, b);
    return max(x,a) <= min(y, b);
}

bool intersect(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    return
        intersect(x0, x1, x2, x3) &&
        intersect(y0, y1, y2, y3) &&
        sign(area(x0, y0, x1, y1, x2, y2)) * sign(area(x0, y0, x1, y1, x3, y3)) <= 0 &&
        sign(area(x2, y2, x3, y3, x0, y0)) * sign(area(x2, y2, x3, y3, x1, y1)) <= 0;
}

int clockwise(int x0, int y0, int x1, int y1, int x2, int y2) {
    return area(x0, y0, x1, y1, x2, y2) < 0;
}

const int mod = 1000000007;

int add(int x, int y) {
    x += y;
    return x >= mod ? x - mod : x;
}

int mul(int x,int y) {
    ll res = 1LL *  x * y;
    return res % mod;
}

int ne(int i, int n) {
    ++i;
    if (i == n)
        i = 0;
    return i;
}
int pr(int i, int n) {
    --i;
    if (i == -1)
        i = n - 1;
    return i;
}

bool inside(int i, int k, const vi& x, const vi& y) {
    int n =  x.size();
    int j = ne(i, n);
    int p = pr(i, n);

    double x0 = x[k] - x[i];
    double y0 = y[k] - y[i];

    double x1 = x[j] - x[i];
    double y1 = y[j] - x[i];

    double x2 = x[p] - x[i];
    double y2 = y[p] - y[i];

    vector<pair<double, int>> a;
    a.push_back(pair<double, int>(atan2(y0, x0), 0));
    a.push_back(pair<double, int>(atan2(y1, x1), 1));
    a.push_back(pair<double, int>(atan2(y2, x2), 2));
    sort(all(a));
    for (int q = 0; q < 3; ++q) {
        int w = ne(q, 3);
        if (fabs(a[w].first-a[q].first) < 1e-9)
            return 0;
    }
    for (int q = 0; q < 3; ++q) {
        int w = ne(q, 3);
        if (a[q].second == 0) {
            return a[w].second == 1;
        }
    }
    return 0;

    /*return
        clockwise(x[i], y[i],
                  x[ne(i, n)], y[ne(i, n)],
                  x[k], y[k]) &&
        clockwise(x[
    return clockwise(
                  x[ne(i, n)] - x[i],
                  y[ne(i, n)] - y[i],
                  x[k] - x[i],
                  y[k] - y[i],
                  x[pr(i,n)] - x[i],
                  y[pr(i,n)] - y[i]);*/
}

int solve(int i, int j, const vi& x, const vi& y, const vector<vector<bool>> &good, vii& dp) {
    int n = x.size();
    int &res = dp[i][j];
    if (j == i)
        return res = 1;
    if (j == ne(i,n)) {
        return res = 1 - (x[i] == x[j] && y[i] == y[j]);
    }
    if (j == ne(ne(i,n), n)) {
        return res = (0 != area(x[i], y[i], x[ne(i,n)], y[ne(i, n)], x[j], y[j]));
    }
    if (res >= 0)
        return res;
    res = 0;
    for (int k = ne(i, n); k != j; k = ne(k, n)) {
        if (good[i][k] && good[k][j]) {
            if ( (k == ne(i, n) || inside(i,k,x,y)) &&
                 (k == pr(j, n) || inside(j,k,x,y))) {
            /*if (((clockwise(x[k], y[k], x[i], y[i], x[ne(i,n)], y[ne(i,n)]) &&
                clockwise(x[k], y[k], x[pr(i,n)], y[pr(i,n)], x[i], y[i])) || k == ne(i, n)) &&
                ((clockwise(x[k], y[k], x[j], y[j], x[ne(j,n)], y[ne(j,n)]) &&
                clockwise(x[k], y[k], x[pr(j,n)], y[pr(j,n)], x[j], y[j])) || k == pr(j, n))) {*/
                //if (pii(x[i], y[i]) == pii(x[j], y[j])
                pii A(x[i], y[i]);
                pii B(x[j], y[j]);
                pii C(x[k], y[k]);
                if (A == B || A == C || B == C)
                    continue;
                debug(i);
                debug(j);
                debug(k);
                res = add(res, mul(solve(i, k, x, y, good, dp), solve(k, j, x, y, good, dp)));
            }

        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vi x(n);
    vi y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    bool ok = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        int k = (i + 2) % n;
        if (area(x[i], y[i], x[j], y[j], x[k], y[k]) != 0) {
            ok = 1;
            if (!clockwise(x[i], y[i], x[j], y[j], x[k], y[k])) {
                reverse(all(x));
                reverse(all(y));
                break;
            }
        }
    }
    if (ok == 0) {
        cout << 0;
        return 0;
    }
    debug(x);
    debug(y);
    vii dp(n, vi(n, -1));
    vector<vector<bool>> good(n, vector<bool> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            good[i][j] = 1;
            for (int k = 0; k < n; ++k) {
                int nk = ne(k, n);
                if (k == i || k == j || nk == i || nk == j) {
                    continue;
                }
                if (intersect(x[k], y[k], x[nk], y[nk],
                              x[i], y[i], x[j], y[j])) {
                    good[i][j] = 0;
                }
            }
        }
    }
    //debug(intersect(x[1], y[1], x[3],y[3], x[4],y[4],x[0], y[0]));
    debug(good);
    cout << solve(0, n - 1, x, y, good, dp) << "\n";
    //debug(inside(0, 3, x,y));


    return 0;
}

