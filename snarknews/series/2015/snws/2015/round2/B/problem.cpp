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

int ss(ll m, int n) {
    int r = 0;
    ll v = 0;
    int p10 = 1;
    int p5 = 1;
    int p2 = 1;
    for (int i = 0; i < n; ++i) {
        p10 *= 10;
        p5 *= 5;
        p2 *= 2;
    }
    for (int i = 1; i <= m; ++i) {
        int x = i;
        while(x) {
            v *= 10;
            x /= 10;
        }
        v += i;
        v %= p10;
        if (v % p2 == 0)
            ++r;
    }
    return r;
}

ll solve(ll m, int n) {
    ll p10 = 1;
    ll p5 = 1;
    for (int i = 0; i < n; ++i) {
        p10 *= 10;
        p5 *= 5;
    }
    ll p = p10;

    ll res = 0;
    ll v = 0;
    for (int i = 1; i <= m && i <= p10; ++i) {
        int x = i;
        while(x) {
            x /= 10;
            v *= 10;
        }
        v += i;
        v %= p;
        //debug(v);
        if ((v & ((1 << n) - 1)) == 0) ++res;
    }
    if (m <= p10)
        return res;
    //debug(ss(mm, n));
    //ll mm = m;
    debug(m);
    debug(res);
    res += 1LL * (m-p) / (1<<n);
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    ll m;
    while(cin >> m >> n) {
        cout << solve(m, n) << "\n";
    }
    return 0;
    while(1) {
        m = rand() % 1000;
        n = rand() % 4;
        ++n;
        ll my = solve(m, n);
        int correct = ss(m,n);
        debug(my);
        debug(correct);
        debug(m);
        debug(n);
        assert(my == correct);
    //cout << res << "\n";
    }

    return 0;
}
