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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#if GCC_VERSION > 40900
using namespace __gnu_pbds;
#endif
using namespace std;

//#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
//#else
//#define debug(x) ;
//#endif

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


const int mod = 1000000007;

void add(int& x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}

int mul(ll x, int y) {
    x %= mod;
    return (1LL*x*y) % mod;
}

int modpow(int x, int n) {
    int r = 1;
    while (n) {
        if (n & 1) {
            r = mul(x,r);
            --n;
        } else {
            x = mul(x,x);
            n /= 2;
        }
    }
    return r;
}

int inv(int x ) {
    return modpow(x, mod -2 );
}

vi f(ll n, int k) {
    vi res;
    int c = 1;
    res.push_back(c);
    for (int i = 0; i < k; ++i) {
        c = mul(c, n - i);
        c = mul(c, inv(i+1));
        res.push_back(c);
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n,k;
    ll L;
    cin >> n >> L >> k;
    vi a(n);
    for (int i =0 ; i < n; ++i) {
        cin >> a[i];
    }
    vi p(n);
    for (int i =0 ; i < n; ++i) {
        p[i] = i;
    }
    sort(all(p), [&](int i, int j) {
        return a[i] < a[j];
    });

    vii dp(k+1, vi(n,0));
    for (int i = 0; i < n; ++i) {
        dp[1][i] = 1;
    }
    for (int curK = 2; curK <= k; ++curK) {
        int j = 0;
        int sum = 0;
        for (int i: p) {
            while(j < n && a[p[j]] <= a[i]) {
                add(sum, dp[curK-1][p[j]]);
                ++j;
            }
            add(dp[curK][i], sum);
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int len = 1; len <= k; ++len) {
            ll m = (L+n-1)/n;
            if (i >= (L%n) && (L%n))--m;
            m -= len-1;
            if (m < 0) {
                m = 0;
            }
            add(res, mul(m, dp[len][i]));
        }
    }
    cout <<res << "\n";

    return 0;
}
