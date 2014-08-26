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

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

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

struct Edge {
    int source, target, weight;
    Edge(int source, int target, int weight): source(source), target(target), weight(weight) {
    }
    bool operator<(const Edge& e) const {
        if (weight != e.weight)
            return weight < e.weight;
        if (source != e.source)
            return source < e.source;
        if (target != e.target)
            return target < e.target;
        return false;
    }
};

class DSU {
public:
    explicit DSU(int n):
        par(n), sizes(n) {
            for (int i = 0; i < n; ++i) {
                par[i] = i;
                sizes[i] = 1;
            }
        }
    int getPar(int x) {
        return (x == par[x])? x : par[x] = getPar(par[x]);
    }
    void merge(int x, int y) {
        x = getPar(x);
        y = getPar(y);
        if (x == y)
            return ;
        if (rand() & 1)
            swap(x,y);
        par[x] = y;
        sizes[y] += sizes[x];
    }
    vi par;
    vi sizes;
};

/*ll res;
void dfs(int v, const vector<vector<pii>>& al, vi& subtreeSize, int p = -1, int weight = -1) {
    subtreeSize[v] = 1;
    for (int i = 0; i < al[v].size(); ++i) {
        int v2 = al[v][i].first;
        int w = al[v][i].second;
        if (v2 == p)
            continue;
        dfs(v2, al, subtreeSize, v, w);
        subtreeSize[v] += subtreeSize[v2];
    }
    int n = al.size();
    res += w *
}*/

int main() {
    int n, m;
    cin >> n >> m;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<Edge> e;
    for (int i = 0; i < m; ++i) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        e.push_back(Edge(x,y,min(a[x], a[y])));
        e.push_back(Edge(y,x,min(a[x], a[y])));
    }
    sort(all(e));
    reverse(all(e));
    DSU dsu(n);
    //vector<vector<pii>> al(n);

    //vector<Edge> taken;
    double res = 0;
    for (int i = 0; i <e.size(); ++i) {
        int s,t;
        s = e[i].source;
        t = e[i].target;
        if (dsu.getPar(s) == dsu.getPar(t)) {
            continue;
        }
        res += 1.0 * dsu.sizes[dsu.getPar(s)] * dsu.sizes[dsu.getPar(t)] * e[i].weight;

        dsu.merge(s,t);
        //al[s].push_back(pii(t, e[i].weight));
        //al[t].push_back(pii(s, e[i].weight));
        //taken.push_back(e[i]);
    }
    printf("%0.18lf\n", 2.0 * res / (n) / (n-1));
    /*sort(all(taken));
    reverse(all(taken));
    ll res = 0;
    for (int i = 0; i < taken.size(); ++i) {
        res +=
    }*/

    return 0;
}

