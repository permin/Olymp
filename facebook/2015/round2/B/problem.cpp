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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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

int C[21][21];

double binom(double p, int s, int n) {
    double x = 0.0;
    x += log(1.0 * C[n][s]);
    x += s * log(p);
    x += (n - s) * log(1.0 - p);
    return std::exp(x);
}

double solve(int n, vector<double>& dp, double p) {
    if (n == 0)
        return 0.0;
    double&res = dp[n];
    if (res >= 0)
        return res;
    res = 1.0;
    for (int i = 1; i <= n; ++i) {
        res += binom(p, i, n) * solve(n - i, dp, p);
    }
    res /= 1.0 - binom(p, 0, n);
    return res;
}

void solve() {
    double p;
    cin >> p;
    if (p >= 1 - EPS) {
        cout << "1.0\n";
        return;
    }
    vector<double> dp(21, -1.0);
    double res = solve(20, dp, p);
    printf("%0.5lf\n", res);
}

int main() {
    for (int n = 0; n <= 20; ++n) {
        for (int k = 0; k <= n; ++k) {
            C[n][k] = (n == 0 || n == k) ? 1 : (C[n - 1][k - 1] + C[n - 1][k]);
        }
    }
    debug(C[20][10]);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<< t + 1 << ": ";
        solve();
    }

    return 0;
}
