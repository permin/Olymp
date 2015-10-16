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
const int INF = 100*1000;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

int iterations;

void dfs(int v, const vii& al, vii& childs, vi& leafs, vii& sizes, int p = -1) {
    for (int v2: al[v]) {
        if (v2 == p)
            continue;
        dfs(v2, al, childs, leafs, sizes, v);
        childs[v].push_back(v2);
        leafs[v] += leafs[v2];
    }
    if (childs[v].empty())
        leafs[v] += 1;
    int c = (int)childs[v].size() + 1;
    sizes[v].resize(c);
    for (int i = c - 2; i >= 0; --i) {
         sizes[v][i] = sizes[v][i+1] + leafs[childs[v][i]];
    }
}

int solve(int v, int pos, int need, int color,
        viii& dp1, viii& dp2, const vii& childs, const vi& leafs,
        const vii& sizes) {
    if (childs[v].empty()) {
        if (color == need) {
            return 0;
        } else {
            return INF;
        }
    }
    int &res = color? dp2[v][pos][need] : dp1[v][pos][need];
    if (res >= 0)
        return res;
    res = INF;
    if (pos == (int)childs[v].size()) {
        if (need == 0) {
            return res = 0;
        } else {
            return res = INF;
        }
    }
    int v2 = childs[v][pos];
    for (int i = max(0, -sizes[v][pos+1] + need); i <= need && i <= leafs[v2]; ++i) {
        iterations += 1;
        res = min(res, solve(v2, 0, i, color, dp1, dp2, childs, leafs, sizes) +
                       solve(v, pos + 1, need - i, color, dp1, dp2, childs, leafs, sizes));

        res = min(res, 1+solve(v2, 0, i, 1^color, dp1, dp2, childs, leafs, sizes) +
                       solve(v, pos + 1, need - i, color, dp1, dp2, childs, leafs, sizes));
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vii al(n);
    for (int i = 0; i < n - 1; ++i) {
        int a,b;
        cin >> a >> b;
        --a;--b;
        al[a].push_back(b);
        al[b].push_back(a);
    }
    vii childs(n);
    vi leafs(n);
    int root = 0;
    for (int i = 0; i < n; ++i) {
        if (al[i].size() > al[root].size()) {
            root = i;
        }
    }
    if (n == 2) {
        cout << "1\n";
        return 0;
    }
    debug(root + 1);
    vii sizes(n);
    dfs(root, al, childs, leafs, sizes);

    viii dp1(n);
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j <= childs[i].size(); ++j) {
            dp1[i].emplace_back(1+min(leafs[root]/2,leafs[i]), -1);
        }
    }
    viii dp2 = dp1;
    cout << solve(root, 0, leafs[root]/2, 0, dp1, dp2, childs, leafs, sizes) << "\n";
    debug(iterations);
    return 0;
}
