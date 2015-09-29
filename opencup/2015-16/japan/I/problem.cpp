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
const long long LLINF = INF;

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

const int N = 4001;
ll dp[N][N];

ll sqr(int x) {
    return 1LL * x * x;
}

struct MaxLin {

    vector<ll> from;
    vector<ll> a;
    vector<ll> b;

    void add(ll aa, ll bb) {
        assert(a.empty() || a.back() <= aa);
        while(!from.empty()) {
            ll x = from.back();
            if (aa * x + bb >= a.back() * x + b.back()) {
                a.pop_back();
                b.pop_back();
                from.pop_back();
            } else {
                break;
            }
        }
        if (from.empty()) {
            from.push_back(-LLINF);
        } else {
            if (a.back() == aa) {
                return;
            }
            // Where are lines crossed
            if (b.back() - bb < 0) {
                from.push_back((b.back() - bb) / (aa - a.back()));
            } else {
                from.push_back((b.back() - bb + aa - a.back() - 1) / (aa - a.back()));
            }
        }
        a.push_back(aa);
        b.push_back(bb);
    }
    ll req(ll x) {
        size_t pos = std::distance(
                from.begin(),
                std::upper_bound(all(from), x));
        --pos;
        return a[pos] * x + b[pos];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    int n, T;
    cin >> n >> T;
    vector<tuple<int, int, int>> r(n);
    for (int i = 0; i < n; ++i) {
        int x,y,z;
        cin >> x >> y>> z;
        r[i] = make_tuple(z,y,x);
    }
    sort(r.begin(), r.end());
    vector<int> f(n);
    vector<int> t(n);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        f[i] = std::get<0>(r[i]);
        t[i] = std::get<2>(r[i]);
        p[i] = std::get<1>(r[i]);
    }

    // dp[n][time]
    // how many point could we got if are able to play
    // songs 0..n-1, and n was the last played song
    for (int time = 1; time <= T; ++time) {
        MaxLin maxLin;

        for (int i = 0; i < n; ++i) {
            ll& res = dp[i][time];
            if (!maxLin.a.empty()) {
                res = maxLin.req(f[i]) - sqr(f[i]);
            }

            // stop here
            res = max(0LL, res);

            if (time - t[i] < 0) {
                continue;
            }
            maxLin.add(2 * f[i],
                    dp[i][time - t[i]] + p[i] - sqr(f[i]));
        }
    }
    ll res = 0;
    debug(t);
    for (int i = 0; i < n; ++i) {
        if (T - t[i] >= 0) {
            debug(p[i]);
            res = max(res, p[i] + dp[i][T - t[i]]);
        }
    }
    cout << res << "\n";


    return 0;
}
