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

class DSU {
public:
    explicit DSU(int n) {
        for (int i = 0; i < n; ++i)
            par.push_back(i);
    }

    int getPar(int x) {
        return x == par[x] ? x : par[x] = getPar(par[x]);
    }

    void merge(int x, int y) {
        x = getPar(x);
        y = getPar(y);
        par[x] = y;
    }

private:
    vi par;
};

int solve(int v, vi& ans, const vii& cond) {
    if (ans[v] >= 0)
        return ans[v];
    for (int v2: cond[v]) {
        ans[v] = max(ans[v], 1 + solve(v2, ans, cond));
    }
    return ans[v];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vi p(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    vii al(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        al[x].push_back(y);
        swap(x,y);
        al[x].push_back(y);
    }

    vii tr(n);
    DSU dsu(n);

    for (int v = 0; v < n; ++v) {
        vector<pii> pv;
        for (int v2: al[v]) {
            pv.emplace_back(p[v2], v2);
            if (p[v] == p[v2]) {
                dsu.merge(v, v2);
            } else {
                if (p[v] < p[v2]) {
                    tr[v].push_back(v2);
                } else {
                    tr[v2].push_back(v);
                }
            }
        }
        sort(all(pv));
        for (int i = 1; i < (int)pv.size(); ++i) {
            if (pv[i - 1].first == pv[i].first) {
                dsu.merge(pv[i - 1].second, pv[i].second);
            } else {
                if (pv[i - 1].first < pv[i].first) {
                    tr[pv[i - 1].second].push_back(pv[i].second);
                } else {
                    tr[pv[i].second].push_back(pv[i - 1].second);
                }
            }
        }
    }
    map<int, int> roots;
    for (int i = 0; i < n; ++i) {
        if (dsu.getPar(i) == i) {
            int id = (int) roots.size();
            roots[i] = id;
        }
    }
    vii cond(roots.size());
    vi in(roots.size());
    vi mass(roots.size());

    for (int v = 0; v < (int)tr.size(); ++v) {
        for (int v2: tr[v]) {
            assert(dsu.getPar(v) != dsu.getPar(v2));
            assert(roots.count(dsu.getPar(v)));
            assert(roots.count(dsu.getPar(v2)));

            // TRANS
            cond[roots[dsu.getPar(v2)]].push_back(
                    roots[dsu.getPar(v)]);

            in[roots[dsu.getPar(v2)]] += 1;
        }
        mass[roots[dsu.getPar(v)]] += 1;
    }

    vi ans(cond.size(), -1);
    for (int i = 0; i < (int) in.size(); ++i) {
        if (in[i] == 0) {
            ans[i] = 1;
        }
    }
    ll res = 0;
    for (int i = 0; i < (int) in.size(); ++i) {
        //debug(i);
        res += 1LL * mass[i] * solve(i, ans, cond);
    }
    cout << res << "\n";


    return 0;
}
