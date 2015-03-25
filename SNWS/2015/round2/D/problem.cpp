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
const int INF = std::numeric_limits<int>::max() / 2 - 42;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

vector<int> dijkstra(int s, const vector<vector<pii>>& al) {
    vector<int> dist(al.size(), INF);
    dist[s] = 0;
    set<pii> Q;
    Q.insert(pii(dist[s], s));
    while(!Q.empty()) {
        int v = Q.begin()->second;
        Q.erase(Q.begin());
        for (pii v2d: al[v]) {
            int v2 = v2d.first;
            int cost = v2d.second;
            int nd = dist[v] + cost;
            if (nd < dist[v2]) {
                Q.erase(pii(dist[v2], v2));
                dist[v2] = nd;
                Q.insert(pii(dist[v2], v2));
            }
        }
    }
    return dist;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int a,b;
    cin >> a >> b;
    --a;--b;
    vector<pair<pii, pii>> edges(m);
    vector<vector<pii>> al(n);
    vector<vector<pii>> tal(n);
    for (int i =0 ; i < m; ++i) {
        int x,y, cost, len;
        cin >> x >> y >> len >> cost;
        --x;
        --y;
        al[x].push_back(pii(y, len));
        tal[y].push_back(pii(x, len));
        edges[i] = make_pair(pii(x,y), pii(len, cost));
    }
    vi da = dijkstra(a, al);
    vi db = dijkstra(b, tal);
    debug(da);
    debug(db);
    vector<pair<int, int>> be;
    for (int i =0 ; i < m; ++i) {
        int x = edges[i].first.first;
        int y = edges[i].first.second;
        int len = edges[i].second.first;
        int cost = edges[i].second.second;

        int totalLength = da[x] + db[y];
        totalLength = min(totalLength, INF);
        totalLength += len;
        be.push_back(pii(totalLength, cost));
    }
    sort(all(be));
    debug(be);
    vector<int> sums(be.size() + 1);
    for (int i = 0; i < be.size(); ++i) {
        sums[i + 1] = sums[i] + be[i].second;
    }
    int q;
    cin >> q;
    while(q-->0) {
        int r;
        cin >> r;
        cout << sums[std::distance(be.begin(),
                upper_bound(all(be), pii(r, INF)))] << "\n";
    }
    return 0;
}
