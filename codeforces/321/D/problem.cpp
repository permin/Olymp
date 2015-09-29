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

ll res;
int a[20];
int am[20][20];
int n;

ll dp[20][1<<18];

/*void go(int v, int mask, int rem, ll cur) {
    res = max(res, cur);
    if (rem <= 0)
        return;
    for (int i = 0; i < n; ++i) {
        if (mask & (1<< i))
            continue;
        go(i, mask | (1 << i), rem - 1, cur + a[i] + am[v][i]);
    }
}*/

ll go(int v, int mask, int rem) {
    ll& ans = dp[v][mask];
    if (ans >= 0)
        return ans;
    if (rem == 0) {
        return ans = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (mask & (1<< i))
            continue;
        ans = max(ans, a[i] + am[v][i] + go(i, mask | (1 << i), rem - 1));
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int m, k;
    cin >> n >> m >> k;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i) {
        int x,y;
        cin >> x>> y;
        --x;--y;
        cin >> am[x][y];
    }
    for (int i = 0; i < n; ++i) {
        debug(i);
        res = max(res, go(i, 1<<i, m - 1) + a[i]);
    }
    cout << res << "\n";


    return 0;
}
