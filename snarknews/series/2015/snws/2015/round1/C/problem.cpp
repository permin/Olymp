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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

const int MaxN = 10e6 + 2;
ll max1[MaxN];
ll max2[MaxN];

void dfs(int v, int p, const vector<vector<pii>>& al) {
    max1[v] = max2[v] = 0;
    for (int i = 0; i <al[v].size(); ++i) {
        int v2 = al[v][i].first;
        int cost = al[v][i].second;
        if (v2 == p)
            continue;
        dfs(v2, v, al);
        ll a = 1LL * cost + max1[v2];
        ll b = max1[v];
        ll c = max2[v];
        while (true) {
            if (a >= b && b >= c)
                break;
            if (a < b)
                swap(a, b);
            if (b < c)
                swap(b, c);
        }
        max1[v] = a;
        max2[v] = b;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<pii>> al(n);
    for (int i =1 ; i < n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        --x;
        --y;
        al[x].push_back(pii(y, z));
        al[y].push_back(pii(x, z));
    }
    dfs(0, -1, al);
    ll res = 0;
    for (int i = 0; i < n; ++i)
        res = max(res, max1[i] + max2[i]);
    cout << res << "\n";
    return 0;
}
