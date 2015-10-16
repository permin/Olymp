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

ll f(int d, const vi& a) {
    int n = (int)a.size();
    vi good(n+n);
    for (int i = 0; i < d; ++i) {
        int M = -1;
        for (int j = i; j < n; j += d) {
            M = max(M, a[j]);
        }
        for (int j = i; j < n; j += d) {
            good[j] = M == a[j];
            good[n+j] = M == a[j];
        }
    }

    vi dp(n+n + 1);
    for (int i = n+n - 1; i >= 0; --i) {
        if (good[i] == 1) {
            dp[i] = 1 + dp[i + 1];
        }
    }
    debug(good);
    debug(dp);
    ll res = 0;
    int n_ = n / d;
    vi stat(n_);
    for (int i = 1; i < n_; ++i) {
        stat[i] = stat[i-1] + (__gcd(i, n_) == 1?  1: 0);
    }

    for (int i = 0; i < n; ++i) {
        int av = min(n - 1, dp[i]);
        res += stat[av / d];
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll res = 0;

    for (int d = 1; d <= n; ++d) {
        if (n % d == 0) {
           debug(d);
           ll cur = f(d,a);
           debug(cur);
           res += cur;
        }
    }
    cout << res << "\n";
    return 0;
}
