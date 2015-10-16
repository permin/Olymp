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

void mul(const vii& a, const vii& b, vii &c) {
    size_t n = a.size();
    c.assign(n, vi(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            for (size_t k = i; k <= j; ++k) {
                c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
            }
        }
    }
}

vii pow(vii a, int n) {
    vii r = a;
    --n;
    while(n > 0) {
        if (n & 1) {
            vii c;
            mul(a, r, c);
            r = c;
            --n;
        } else {
            vii c;
            mul(a, a, c);
            a = c;
            n >>= 1;
        }
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, T;
    cin >> n >> T;


    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vi u(a);
    sort(all(u));
    u.erase(unique(all(u)), u.end());

    vii dp(n, vi(n));
    for (int d = 0; d < n; ++d) {
        for (int i = 0; i + d < n; ++i) {
            int j = i + d;
            if (d == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = 2 * (a[i] <= a[j]);
                for (int k = i + 1; k < j; ++k) {
                    if (a[i] <= a[k] && a[k] <= a[j]) {
                        dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] - 1);
                    }
                }
            }
        }
    }

    vii num(u.size(), vi(u.size()));
    for (size_t i = 0; i < u.size(); ++i) {
        for (size_t j = 0; j < u.size(); ++j) {
            int b = -1;
            int e = -1;
            for (int k = 0; k < n; ++k) {
                if (a[k] == u[i] && b == -1)
                    b = k;
                if (a[k] == u[j])
                    e = k;
            }
            assert(min(b,e) >= 0);
            num[i][j] = dp[b][e];
        }
    }
    for (size_t i = 0; i < u.size(); ++i) {
        for (size_t j = 1; j < u.size(); ++j) {
            num[i][j] = max(num[i][j], num[i][int(j)-1]);
        }
    }

    debug(num);

    vii r = pow(num, T);
    debug(pow(num, 1));
    debug(pow(num, 2));
    debug(pow(num, 3));
    int m = 0;
    for (auto x: r)
        for (int y: x)
            m = max(m, y);
    cout << m << "\n";

    return 0;
}
