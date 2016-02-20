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
#include <utility>

#if GCC_VERSION > 40900
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#endif
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;};

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

double T;
bool around;

double solve(int len, int r, double th0, int v) {
    debug(th0);
    double lo = 0;
    double up = 3e9;
    int iters = 50;
    if (around) {
        lo = 0.9 * T - 10;
        lo = max(lo, 0.0);
        up = 1.1 * T + 10;
        iters = 10;
    }
    for (int i = 0; i < iters; ++i) {
        double t = 0.5 * (up + lo);
        if (v * t + r * cos(1.0 * v / r * t + th0) - r * cos(th0) > 1.0 * len) {
            up = t;
        } else {
            lo = t;
        }
    }
    return 0.5 * (lo + up);
}


double solve(double lo, double up, int len, int r, int v) {
    if (up - lo < 1e-3) {
        return solve(len, r, 0.5 * (lo+up), v);
    }
    int at = -1;
    double res = 5e9;
    const int M = 30;
    double dx = (up - lo) / M;
    for (int it = 0; it < M; ++it) {
        double cur = solve(len, r, 1.0 * it * dx + lo, v);
        if (res > cur) {
            res = cur;
            at = it;
        }
    }
    double answer = 5e9;
    if (at == 0) {
        answer = min(answer, solve(lo + (M - 1) * dx, lo + (M) * dx, len, r, v));
    } else {
        answer = min(answer, solve(lo + (at - 1) * dx, lo + (at) * dx, len, r, v));
    }
    debug(at);
    answer = min(answer, solve(lo + (at) * dx, lo + (at + 1) * dx, len, r, v));
    return answer;
}

void solve(int len, int r, int v) {
    around = 0;
    T = solve(len, r, 0, v);
    around = 1;
    printf("%0.18lf\n", solve(0, 2.0 * PI, len, r, v));
    return;
    double lo = 0.0;
    double up = 2.0 * PI;
    while(1) {
        int at = -1;
        double res = 5e9;
        const int M = 100;
        double dx = (up - lo) / M;
        for (int it = 0; it < M; ++it) {
            double cur = solve(len, r, 1.0 * it * dx + lo, v);
            if (res > cur) {
                res = cur;
                at = it;
            }
        }
        debug(at);
        cout << res << "\n";
        return ;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, r, v;
    cin >> n >> r >> v;
    for (int i = 0; i < n; ++i) {
        int f,s;
        cin >> f >> s;
        solve(s-f, r, v);
    }
    return 0;
    for (int i = 0; i < 100 * 1000; ++i) {
        if (i % 1000 == 0)
            debug(i);
        solve(200000, r, v);
    }
    return 0;
}
