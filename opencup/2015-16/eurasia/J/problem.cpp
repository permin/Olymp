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

int W,H;
// W - x

vector<pii> neigh(const pii& p) {
    vector<pii> r;
    int x = p.first;
    int y = p.second;
    r.emplace_back(x + 1, y);
    r.emplace_back(x, y+1);
    r.emplace_back(x - 1, y);
    r.emplace_back(x, y-1);
    r.emplace_back(x - 1, y+1);
    r.emplace_back(x+1, y-1);
    return r;
}

bool ok(const pii& A) {
    return 0 <= A.first && A.first < W &&
        0 <= A.second&& A.second< H;
}

set<pii> bfs(const pii& o, int r, const set<pii>& f) {
    map<pii, int> dist;
    dist[o] = 0;
    queue<pii> Q;
    Q.push(o);
    while(!Q.empty()) {
        pii v = Q.front();
        Q.pop();
        if (dist[v] == r)
            continue;
        for (const pii& v2: neigh(v)) {
            if (!ok(v2)) {
                continue;
            }
            if (f.count(v2)) {
                continue;
            }
            if (dist.count(v2) == 0) {
                dist[v2] = dist[v] + 1;
                Q.push(v2);
            }
        }
    }
    set<pii> out;
    for (auto& kv: dist) {
        out.insert(kv.first);
    }
    return out;
}

struct Edge {
    int target;
    int cap;
    int backEdge;
    int flow = 0;
};

void addEdge(vector<vector<Edge>>& al, int source, int target, int c) {
    Edge e, eBack;
    e.target = target;
    e.cap = c;
    e.flow = 0;

    eBack.target = source;
    eBack.cap = 0;
    eBack.flow = 0;

    e.backEdge = (int)al[target].size();
    eBack.backEdge = (int)al[source].size();
    al[source].push_back(e);
    al[target].push_back(eBack);
}

int maxFlow(vector<vector<Edge>>& al, int source, int sink)  {
    int flow = 0;
    int n = (int)al.size();
    while(true) {
        vi dist(n, INF);
        vi prev(n, -1);
        vi incEdge(n, -1);
        dist[source] = 0;
        queue<int> Q;
        Q.push(source);
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            int i = 0;
            for (const Edge& e: al[v]) {
                if (e.cap > 0) {
                    int v2 = e.target;
                    if (dist[v2] == INF) {
                        dist[v2] = dist[v] + 1;
                        Q.push(v2);
                        incEdge[v2] = i;
                        prev[v2] = v;
                    }
                }
                ++i;
            }
        }
        if (dist[sink] == INF)
            break;

        int cur = sink;
        while(cur != source) {
            // v -> v2
            int v = prev[cur];
            int v2 = cur;

            Edge& e = al[v][incEdge[v2]];
            e.cap -= 1;
            e.flow += 1;
            al[v2][e.backEdge].cap += 1;
            al[v2][e.backEdge].flow -= 1;

            cur = v;
        }
        flow += 1;
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin >> W >> H;
    int n;
    cin >> n;
    vi cityX(n);
    vi cityY(n);
    vi cityP(n);
    set<pii> cities;
    for (int i = 0; i <n; ++i) {
        cin >> cityX[i] >> cityY[i] >> cityP[i];
        cities.emplace(cityX[i], cityY[i]);
    }

    int c;
    cin >> c;
    vi cX(c);
    vi cY(c);
    vi cP(c);
    map<pii, int> catIndex;
    for (int i = 0; i < c; ++i) {
        cin >> cX[i] >> cY[i] >> cP[i];
        catIndex[pii(cX[i], cY[i])] = i;
    }
    set<pii> mount;
    set<pii> forb = cities;
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x,y;
        cin >> x >> y;
        mount.emplace(x,y);
        forb.emplace(x,y);
    }

    set<pii> interesting;
//set<pii> bfs(const pii& o, int r, const set<pii>& f) {
    for (int i = 0; i < n; ++i) {
        set<pii> o = bfs(pii(cityX[i], cityY[i]), 2, set<pii>());
        for (const auto& a: o) {
            if (cities.count(a) == 0 && mount.count(a) == 0) {
                interesting.insert(a);
            }
        }
    }
    debug(interesting);
    map<pii, int> idInt;
    vector<pii> interestingArray;
    for (const pii& a: interesting) {
        int id = (int)idInt.size();
        interestingArray.push_back(a);
        idInt[a] = id;
    }

    int intSize = (int)idInt.size();
    int source = c + (int)idInt.size() +intSize + n;
    int sink = source + 1;
    vector<vector<Edge>> al(sink + 1);

    for (int i = 0; i < c; ++i) {
        set<pii> o = bfs(pii(cX[i], cY[i]), cP[i]-1, forb);
        debug(i);
        debug(o);
        for (const pii& a: o) {
            if (interesting.count(a)) {
                addEdge(al, i, c + idInt[a], 1);
            }
        }
        addEdge(al, source, i, 1);
    }

    for (int i = 0; i < intSize; ++i) {
        addEdge(al, c + i, c + intSize + i, 1);
    }
    for (int i = 0; i < n; ++i) {
        set<pii> o = bfs(pii(cityX[i], cityY[i]), 2, set<pii>());
        for (const auto& a: o) {
            if (cities.count(a) == 0 && mount.count(a) == 0) {
                addEdge(al, c + idInt[a] + intSize, c + intSize + (int)idInt.size() + i, 1);
            }
        }
    }

    int res = 0;

    vector<pii> outCat(c, pii(-1,-1));
    vi cityToBomb(c, -1);

    for (int mask = 1; mask < (1<<n); ++mask) {
        vector<vector<Edge>> alCopy = al;
        int num = 0;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                ++num;
                addEdge(alCopy, c + intSize + (int)idInt.size() + i, sink, cityP[i]);
                total += cityP[i];
            }
        }
        int flow = maxFlow(alCopy, source, sink);
        debug(mask);
        debug(flow);
        debug(total);
        if (flow == total) {
            if (num > res) {
                outCat.assign(c, pii(-1,-1));
                cityToBomb.assign(c, -1);
                for (int i = 0; i< c; ++i) {
                    for (const Edge& e: alCopy[i]) {
                        if (e.flow > 0) {
                            int intPoint = e.target;
                            outCat[i] = interestingArray[intPoint - c];
                            for (const Edge& e3: alCopy[intPoint]) {
                                for (const Edge& e2: alCopy[e3.target]) {
                                    if (e2.flow > 0) {
                                        cityToBomb[i] = e2.target - c - (int)interesting.size() - intSize;
                                    }
                                }
                            }
                        }
                    }
                }
                res = num;
            }
        }
    }

    for (int it = 0; it < c; ++it) {
        for (int i = 0; i < c; ++i) {
            pii to = outCat[i];
            if (catIndex.count(to)) {
                int j = catIndex[to];
                if (outCat[j] == pii(-1,-1)) {
                    outCat[j] = outCat[i];
                    cityToBomb[j] = cityToBomb[i];

                    outCat[i] = pii(-1,-1);
                    cityToBomb[i] = -1;
                }
            }
        }
    }

    cout << res << "\n";
    for (int i = 0; i < c; ++i) {
        if (cityToBomb[i] != -1) {
            cout << outCat[i].first << " " << outCat[i].second << " " << 1 + cityToBomb[i];
        } else {
            cout << cX[i] << " " << cY[i] << " " << 0;
        }
        cout << "\n";
    }
    return 0;
}
