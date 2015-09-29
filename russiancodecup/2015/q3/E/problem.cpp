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

ll gcd(ll a, ll b) {
    a = std::abs(a);
    b = std::abs(b);
    while(a) {
        b %= a;
        swap(a,b);
    }
    return b;
}

pii f(int x, int y, int x1, int y1) {
    int dx = x - x1;
    int dy = y - y1;

    if (dx < 0) {
        dx *= -1;
        dy *= -1;
    }

    if (dx == 0) {
        dy = 1;
    }

    if (dy == 0) {
        dx = 1;
    }

    int d = (int)gcd(dx, dy);
    dx /= d;
    dy /= d;
    return pii(dx, dy);
}

struct F {
    map<int, int> id;
    vii al;
    int get(int i) {
        if (id.count(i) == 0) {
            int s = (int) id.size();
            id[i] = s;
            al.emplace_back();
        }
        return id[i];
    }
};

int dfs(int v, const vii& al, vector<bool>& u) {
    if (u[v])
        return 0;
    int r = 1;
    u[v] = 1;
    for (int v2: al[v]) {
        r += dfs(v2, al, u);
    }
    return r;
}

int solve(const vii& al, int& k) {
    //debug(al);
    vi c;
    vector<bool> used(al.size());
    for (int i = 0; i < int(al.size()); ++i) {
        if (!used[i])
            c.push_back(dfs(i, al, used));
    }
    sort(all(c));
    if (c.size() == 1) {
        k = 1;
        return c.back();
    }
    k = 2;
    return c.back() + *std::next(c.rbegin());
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t-->0) {
    int n;
    cin >> n;
    vi x(n);
    vi y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    std::map<pii, F> s;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            pii key = f(x[i],y[i],x[j],y[j]);
            int a = s[key].get(i);
            int b = s[key].get(j);
            s[key].al[a].push_back(b);
            s[key].al[b].push_back(a);
        }
    }
    int res = 1;
    if (n > 1) res = 2;
    for (const auto& kv: s) {
        int k;
        int r = solve(kv.second.al, k);
        if (k == 1 && r < n)
            ++r;
        res = max(res, r);
    }
    cout << res << "\n";
    }



    return 0;
}
