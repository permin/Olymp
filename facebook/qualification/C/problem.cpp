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

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

typedef vector<double> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

int r() {
    char buf[22];
    cin >> buf;
    int x,y;
    sscanf(buf, "%d.%d", &x,&y);
    return x * 1000 + y;
}

int ps, pr, pi,pu,pw,pd,pl;
int k;

double solve(int a, int b, int p, viii& cache) {
    if (p < 0)
        p = 0;
    if (p > 1000)
        p = 1000;
    double& res = cache[a][b][p];
    if (res >= 0)
        return res;
    if (a == k)
        return res = 1.0;
    if (b == k)
        return res = 0.0;
    res = 0;
    for (size_t rain = 0; rain < 2; ++rain) {
        for (size_t win = 0; win < 2; ++win) {
            for (int inc = 0; inc < 2; ++inc) {
                double pRain = 1e-3 * (rain ? 1000 - p : p);
                double pWin = 1e-3 * (rain ? pr : ps);
                if (!win)
                    pWin = 1.0 - pWin;
                double pChange = 1e-3 * (win ? pw : pl);
                assert(pWin <=  1);
                assert(pRain <=  1);
                assert(pChange  <=  1);
                if (!inc)
                    pChange = 1 - pChange;
                int add = win ? pu : -pd;
                if (!inc)
                    add = 0;
                res += pRain * pWin * pChange * solve(a + win, b + 1 - win, p + add, cache);
            }
        }
    }

    return res;
}

void solve() {
    cin >> k;
    viii dp(k + 1, vii(k + 1, vi(1001, -1.0)));
    ps=r();
    pr=r();
    pi=r();
    pu=r();
    pw=r();
    pd=r();
    pl=r();
    printf("%0.6lf\n", solve(0,0,pi, dp));

}

int main() {
    size_t tests;
    cin >> tests;
    for (size_t t = 0; t < tests; ++t) {
        cout << "Case #" << t+1 <<": ";
        solve();
    }
    return 0;
}
