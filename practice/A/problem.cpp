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
#include <complex>
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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

void dfs(int v, vi& par, vii& ver, vi& depth, const vii&ch) {
    ver.resize(max<int>(ver.size(), depth[v]+1));
    ver[depth[v]].push_back(v);
    for (int v2: ch[v]) {
        par[v2] = v;
        depth[v2] = 1 + depth[v];
        dfs(v2, par, ver, depth, ch);
    }
}

int up(int v, int p, const vii& dp) {
    int bit = dp.size() - 1;
    while(p) {
        if (p >= (1 << bit)) {
            v = dp[bit][v];
            p -= 1 << bit;
        }
        --bit;
    }
    assert(v != -1);
    return v;
}

int main() {
    while(1)
    {
        int M = 1000* 1000 * 1000;
        int x = rand() % M;
        int y = rand() % M;
        ++x;
        ++y;
        if (1LL * x* y != 1LL * int(x*y) && int(x * y) >= 0) {
            debug(x);
            debug(y);
            debug(x*y);
            debug(476284980*4);
            return 0;
        }
    }
    int n;
    cin >> n;
    vector<vector<int>> childs(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x) {
            childs[x - 1].push_back(i);
        }
    }
    vi par(n, -1);
    vii vertices;
    vi depth(n, -1);
    for (int i = 0; i <n; ++i) {
        if (par[i] == -1) {
            depth[i] = 0;
            dfs(i, par, vertices, depth, childs);
        }
    }
    vii dp(17, vi(n,-1));
    dp[0] = par;
    for (int i = 1; i < 17; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dp[i - 1][j] != -1) {
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            }
        }
    }
    vi pos(n, -1);
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i].size(); ++j) {
            pos[vertices[i][j]] = j;
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x,p;
        cin >> x >> p;
        --x;
        int res = 0;
        if (depth[x] < p) {
            res = 0;
        } else {
            int xp = pos[x];
            int d = depth[x];
            auto lo = lower_bound(vertices[d].begin(), vertices[d].begin() + xp + 1,
                    x, [&](int a, int b) {
                        return pos[up(a, p, dp)] < pos[up(b, p, dp)];
                    });
            auto upe = upper_bound(vertices[d].begin() + xp, vertices[d].end(),
                    x, [&](int a, int b) {
                        return pos[up(a, p, dp)] < pos[up(b, p, dp)];
                    });
            res = upe - lo;
            --res;
        }
        cout << res << " ";
    }

    return 0;
}
