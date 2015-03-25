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

struct Edge {
    size_t target;
    int cost;
    int cap;
    int back;
};

void minCostMaxFlow(vector<vector<Edge>>& net, int source, int sink) {
    int n = int(net.size());
    vector<ll> phi(n);
    while(true) {
        set<pair<ll, int>> Q;
        vector<ll> dist(n, LLINF);
        vector<int> prevVertex(n, -1);
        vector<int> prevEdge(n, -1);
        dist[source] = 0;
        Q.insert(make_pair(0, source));
        while (!Q.empty()) {
            int v = Q.begin()->second;
            Q.erase(Q.begin());
            for (int i = 0; i < net[v].size(); ++i) {
                const Edge& edge = net[v][i];
                if (edge.cap <= 0)
                    continue;
                ll ne = edge.cost + phi[v] - phi[edge.target];
                assert(ne >= 0);
                ll ndist = dist[v] + ne;
                if (ndist < dist[edge.target]) {
                    Q.erase(make_pair(dist[edge.target], edge.target));
                    prevVertex[edge.target] = v;
                    prevEdge[edge.target] = i;
                    dist[edge.target] = ndist;
                    Q.insert(make_pair(dist[edge.target], edge.target));
                }
            }
        }
        for (int v = 0; v < n; ++v) {
            if (dist[v] != LLINF) {
                phi[v] += dist[v];
            }
        }
        debug(dist);
        if (dist[sink] >= LLINF)
            break;
        int cur = sink;
        vi path;
        while(cur != source) {
            path.push_back(cur);
            int prev = prevVertex[cur];
            Edge& edge = net[prev][prevEdge[cur]];
            edge.cap -= 1;
            net[edge.target][edge.back].cap += 1;
            cur = prev;
        }
        path.push_back(cur);
        reverse(all(path));
        debug(path);
    }
}

void add(int source, int target, int cost, int cap, vector<vector<Edge>>& net) {
    net[source].resize(net[source].size() + 1);
    net[target].resize(net[target].size() + 1);

    net[source].back().target = target;
    net[source].back().cost = cost;
    net[source].back().cap = cap;
    net[source].back().back = int(net[target].size()) - 1;

    net[target].back().target = source;
    net[target].back().cost = -cost;
    net[target].back().cap = 0;
    net[target].back().back = int(net[source].size()) - 1;
}

void solve() {
    int workers = 0;
    int jobs = 0;
    cin >> workers >> jobs;
    vector<vector<Edge>> net(2 + workers + jobs);
    int source = int(net.size()) - 2;
    int sink = int(net.size()) - 1;

    for (int i = 0; i < workers; ++i) {
        for (int j = 0; j < jobs; ++j)
            add(source, i, 2 * j + 1, 1, net);
    }

    for (int j = 0; j < jobs; ++j) {
        add(j + workers, sink, 0, 1, net);
    }

    for (int i = 0; i < workers; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < jobs; ++j) {
            if (s[j] == '1') {
                add(i, j + workers, 0, 1, net);
            }
        }
    }
    minCostMaxFlow(net, source, sink);
    vector<vector<int>> ans(workers);
    for (int i = 0; i < workers; ++i) {
        for (const auto& edge: net[i]) {
            if (edge.cap == 0 && (workers <= edge.target && edge.target < source)) {
                ans[i].push_back(int(edge.target) - workers);
            }
        }
    }
    for (int i = 0; i < workers; ++i) {
        cout << ans[i].size() << " ";
        for (int x: ans[i])
            cout << x + 1 << " ";
        cout << "\n";
    }
}

int main() {
    freopen("work.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    int t;
    t = 1;
    while(t-->0){
        solve();
    }
    return 0;
}
