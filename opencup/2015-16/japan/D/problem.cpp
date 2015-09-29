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


ll gcd(ll x, ll y) {
    while(x) {
        y %= x;
        swap(x,y);
    }
    return y;
}

ll lcm(ll x, ll y) {
    return x / gcd(x,y) * y;
}

ll phi(int p, int n) {
    ll r = p - 1;
    for (int i = 1; i < n; ++i) {
        r *= p;
    }
    return r;
}

int car(int n) {
    ll order = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int x = 0;
            while(n % i == 0) {
                ++x;
                n/=i;
            }
            order = lcm(order, phi(i, x));
        }
    }
    if (n > 1) {
        order = lcm(order, phi(n, 1));
    }
    if (order % 4 == 0)
        order /= 2;
    return (int)order;
}

int phi(int n) {
    ll order = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int x = 0;
            while(n % i == 0) {
                ++x;
                n/=i;
            }
            order = order* phi(i, x);
        }
    }
    if (n > 1) {
        order = order * phi(n, 1);
    }
    return (int)order;
}


int modpow(int x, int n, int mod) {
    int r = 1;
    while(n) {
        if (n & 1) {
            n ^= 1;
            r = int((1LL * r * x) % mod);
        } else {
            n >>= 1;
            x = int((1LL * x * x) % mod);
        }
    }
    return r;
}

/*vector<pair<int, int>> fact(int n) {
    vector<pair<int, int>> r;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int x = 0;
            while(n % i == 0) {
                ++x;
                n/=i;
            }
            r.emplace_back(i, x);
        }
    }
    if (n > 1) {
        r.emplace_back(n, 1);
    }
    return r;
}*/

int solve(int n) {
    if (n == 2) {
        return 1;
    }
    int order = car(n);
    if (gcd(order, n) != 1) {
        return -1;
    }
    int g = phi(order);
    int k = INF;
    for (int i = 1; i * i <= g; ++i) {
        if (g % i != 0)
            continue;
        for (int x: {i, g/i}) {
            if (modpow(n % order, x, order) == 1) {
                k = min(k, x);
            }
        }
    }
    if (k == INF)
        k = -1;
    return k;
}

int main() {
    if (0){
        int n;
        cin >> n;
        debug(phi(n));
    }

    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    cout << solve(n) << "\n";
    return 0;

    /*ll order = ex(n);



    assert(order <= n);
    debug(order);

    auto f = fact(n);
    map<int, int> stat;
    for (auto xy: f) {
        stat[xy.first] = stat[xy.second];
    }
    auto fo = fact((int)order);
    int res = 0;
    for (auto xy: fo) {
        int k = stat[xy.first];
        if (k > 0) {
            res = max(res, (xy.second + k - 1) / k);
        } else {
            res = INF;
        }
    }
    if (res != INF) {
        cout << res << "\n";
    } else {
        cout << "-1\n";
    }*/

    return 0;
}
