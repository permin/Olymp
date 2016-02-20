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

#if GCC_VERSION > 40900
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#endif
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

typedef pii Pos;
struct Edge {
    Pos a, b;
};

bool ok(int x, int y, int n, int m) {
    return (x >= 0 && y >= 0 && x < n && y < m);
}

void appendEdges(const vii& num, int d, vector<Edge>& o) {
    int n = (int)num.size();
    int m = (int)num[0].size();

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (!num[x][y])
                continue;
            for (int nx = max(0,x - d); nx <= x + d && nx < n; ++nx) {
                int dr = d - abs(x-nx);
                for (int ny: {y - dr, y + dr}) {
                    if (ok(nx,ny,n,m)) {
                        if (!num[nx][ny])
                            continue;
                        Edge e;
                        e.a = Pos(x,y);
                        e.b = Pos(nx,ny);
                        o.push_back(e);
                    }
                }
            }
        }
    }
}

void add(set<Pos>& neigh, const Pos& v,  map<Pos, vector<Pos>>& al) {
    for (const Pos& v2: al[v]) {
        neigh.insert(v2);
    }
}

vector<Pos> stable2(map<Pos, vector<Pos>>& al, int k) {
    set<Pos> neigh;
    Pos origin = al.begin()->first;
    vector<Pos> ans(1, origin);
    add(neigh, origin, al);
    for (const auto& kv: al) {
        const Pos& v = kv.first;
        if (v == origin) {
            continue;
        }
        bool ok = 1;
        for (const Pos& v2: al[v]) {
            if (neigh.count(v2)) {
                ok = 0;
                break;
            }
        }
        if (!ok)
            continue;
        add(neigh, v, al);
        ans.push_back(v);
        if (int(ans.size()) > k) {
            break;
        }
    }
    return ans;
}

vector<Pos> kMean(const vii& num, int k) {
    int n = (int)num.size();
    int m = (int)num[0].size();
    map<Pos, vector<Pos>> al;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (!num[x][y]) {
                continue;
            }
            al[Pos(x,y)].resize(0);
        }
    }
    for (int d = 0; ;++d) {
        vector<Edge> edges;
        appendEdges(num, d, edges);
        for (const auto& e: edges) {
            al[e.a].push_back(e.b);
        }
        auto s = stable2(al, k);
        if (s.size() <= k) {
            return s;
        }
    }
}

struct CY {
    bool operator()(const Pos& a, const Pos& b) const {
        return Pos(a.second, a.first) < Pos(b.second, b.first);
    }
};

Pos solveForCluster(const vector<vector<double>>& w, vector<Pos> p, double& pen) {
    //debug(p);
    double totalW = 0.0;
    Pos ans(-1,-1);
    int mx = 1000;
    int my = 10000;
    for (const Pos& pos: p) {
        totalW += w[pos.first][pos.second];
        mx = min(mx, pos.first);
        my = min(my, pos.second);;
    }
    {
        sort(all(p));
        size_t i = 0;
        double wInL = 0.0;
        for (int x = mx; ; ++x) {
            while(i < p.size() && p[i].first <= x) {
                wInL += w[p[i].first][p[i].second];
                ++i;
            }
            if (wInL >= 0.5 * totalW) {
                ans.first = x;
                break;
            }
        }
    }
    {
        sort(all(p), CY());
        size_t i = 0;
        double wInL = 0.0;
        for (int y = my; ; ++y) {
            while(i < p.size() && p[i].second<= y) {
                wInL += w[p[i].first][p[i].second];
                ++i;
            }
            if (wInL >= 0.5 * totalW) {
                ans.second = y;
                break;
            }
        }
    }
    for (const Pos& pos: p) {
        pen +=  w[pos.first][pos.second] * (abs(pos.first - ans.first) + abs(pos.second - ans.second));
    }
    return ans;
}

vector<Pos> solve(const vector<vector<double>>& w, int k, double bound, double& pen) {
    pen = 0.0;
    int n = (int)w.size();
    int m = (int)w[0].size();
    vii num(n, vi(m));
    vii unit(n, vi(m));
    int rem = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (w[x][y] >= bound) {
                num[x][y] = 1;
            }
            if (w[x][y] > 0.0) {
                unit[x][y] = 1;
                ++rem;
            }
        }
    }
    vector<Pos> k_mean = kMean(num, k);
    assert(k_mean.size() <= k);
    if (1) {
        set<Pos> k_mean_dist(all(k_mean));
        int it = 1000 + 2*k;
        while(k_mean_dist.size() < k && it) {
            --it;
            k_mean_dist.emplace(Pos(rand() % n, rand() % m));
        }
        k_mean.assign(all(k_mean_dist));
    }
    sort(all(k_mean));
    vii neigh(n, vi(m, -1));
    debug(k_mean.size());
    vector<Edge> edges;
    for (const Pos& pos: k_mean) {
        if (unit[pos.first][pos.second] == 0) {
            unit[pos.first][pos.second] = 1;
            ++rem;
        }
    }
    for (int d = 0; ; ++d) {
        if (rem == 0)
            break;
        edges.clear();
        appendEdges(unit, d, edges);
        for (const Edge& e: edges) {
            if (neigh[e.a.first][e.a.second] == -1) {
                if (binary_search(all(k_mean), e.b)) {
                    neigh[e.a.first][e.a.second] = int(
                        lower_bound(all(k_mean), e.b) - k_mean.begin());
                    --rem;
                }
            }
        }
    }

    vector<vector<Pos>> clusters(k_mean.size());
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (unit[x][y]) {
                clusters[neigh[x][y]].push_back(Pos(x,y));
            }
        }
    }
    vector<Pos> ans(k_mean.size());
    for (int i = 0; i < (int)k_mean.size(); ++i) {
        ans[i] = solveForCluster(w, clusters[i], pen);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<double>> w(n, vector<double>(m,0.0));
    vector<double> allW;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cin >> w[x][y];
            allW.push_back(w[x][y]);
        }
    }
    vector<Pos> ans;
    double pen = 1e9;
    vector<double> Ws;
    Ws.push_back(1.0);
    Ws.push_back(0.0);
    if (1) {
        sort(all(allW));
        size_t step = allW.size() / 20;
        if (step == 0)
            ++step;
        for (size_t i = 0; i < allW.size(); i += step) {
            Ws.push_back(allW[i]);
        }
        if (0 && n * m < 100)  {
            Ws = allW;
            Ws.push_back(0);
            Ws.push_back(1);
        }
    }
    sort(all(Ws));


    Ws.clear();
    for (int i = 0; i < 100; ++i) {
        Ws.push_back(1.0);
    }
    double bestW = -1.0;
    for (double ww: Ws) {
        debug(ww);
        double curPen = 0.0;
        auto curAns = solve(w, k, ww, curPen);
        debug(curPen);
        if (curPen < pen) {
            bestW = ww;
            pen = curPen;
            ans = curAns;
        }
    }
    debug(pen);
    debug(bestW);
    assert(ans.size() <= k);
    for (auto p: ans) {
        cout << 1 + p.first << " " << 1 + p.second << "\n";
    }


    return 0;
}
