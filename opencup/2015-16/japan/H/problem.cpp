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
const double LLINF = 1.0 * INF;

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

double sqr(int x) {
    return 1.0 * x * x;
}

double distC(int x, int y, int x1, int y1) {
    return sqrt(
            sqr(x-x1) + sqr(y-y1));
}

struct Edge {
    int from;
    int to;
    int capacity;
    double cost;
    int flow;
    int backEdgeIndex;
    void addFlow(int f) {
        assert(capacity >= f);
        capacity -= f;
        flow += f;
    }
};

vector<double> fordBelman(int source, const vector<vector<Edge> >& net, vector<pii>& prev, const vector<double>& ) {
    int vertices = (int)net.size();
    vector<double> dist(vertices, LLINF);
    prev.assign(vertices, pii(source, -1));
    dist[source] = 0;
    queue<int> Q;
    Q.push(source);
    while(!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (size_t i = 0; i < net[v].size(); ++i) {
            const Edge& e = net[v][i];
            int v2 = e.to;
            if (e.capacity > 0) {
                double newDist = dist[v] + e.cost;
                if (dist[v2] > newDist) {
                    dist[v2] = newDist;
                    prev[v2] = pii(v, i);
                    Q.push(v2);
                }
            }
        }
    }
    return dist;
}

vector<double> dijkstra2(int source, const vector<vector<Edge> >& net, vector<pii>& prev, const vector<double>& phi) {
    int vertices = (int)net.size();
    vector<double> dist(vertices, LLINF);
    prev.assign(vertices, pii(source, -1));
    dist[source] = 0;
    vector<bool> killed(vertices, false);
    for (int i = 0; i < vertices; ++i) {
        int minAt = -1;
        for (int j = 0; j < vertices; ++j) {
            if (killed[j])
                continue;
            if (minAt == -1 || dist[minAt] > dist[j])
                minAt = j;
        }
        killed[minAt] = 1;
        for (size_t j = 0; j < net[minAt].size(); ++j) {
            const Edge& e = net[minAt][j];
            int v2 = e.to;
            if (e.capacity > 0) {
                double newDist = phi[minAt] + dist[minAt] + e.cost - phi[v2];
                if (dist[v2] > newDist) {
                    dist[v2] = newDist;
                    prev[v2] = pii(minAt, j);
                }
            }
        }
    }
    return dist;
}

template <class Finder>
void minCostMaxFlow(vector<vector<Edge> >& net, Finder finder, int source, int sink, int k=std::numeric_limits<int>::max()) {
    //int vertices = net.size();
    vector<double> phi;
    if (1) {
        vector<pii> dummy;
        vector<double> dummyPhi;
        phi = fordBelman(source, net, dummy, dummyPhi);
    }
    while (k) {
        vector<pii> prev;
        vector<double> dist = finder(source, net, prev, phi);
        if (dist[sink] >= LLINF - 1)
            break;
        //debug(dist[sink]);
        for (size_t i = 0; i < dist.size(); ++i) {
            phi[i] += dist[i];
        }
        int add = INF;
        for (int last = sink; prev[last].first != last; last = prev[last].first) {
            int v = prev[last].first;
            int edgeIndex = prev[last].second;
            int v2 = last;
            add = min(add, net[v][edgeIndex].capacity);
            assert(v2 == net[v][edgeIndex].to);
        }
        if (k < add)
            add = k;
        k -= add;
        assert(add);
        for (int last = sink; prev[last].first != last; last = prev[last].first) {
            int v = prev[last].first;
            int edgeIndex = prev[last].second;
            int v2 = last;
            //debug(net[v][edgeIndex].index);
            net[v][edgeIndex].addFlow(add);
            net[v2][net[v][edgeIndex].backEdgeIndex].addFlow(-add);
        }
    }
}

double cost(vector<vector<Edge> >& net) {
    double res = 0;
    for (size_t i = 0; i < net.size(); ++i) {
        for (size_t j = 0; j < net[i].size(); ++j) {
            if (net[i][j].flow > 0) {
                res += 1LL * net[i][j].flow * net[i][j].cost;
            }
        }
    }
    return res;
}

void addEdge(vector<vector<Edge> >& net, int v, int v2, int cap, double co) {
    assert(cap > 0);
    net[v].push_back(Edge());
    net[v2].push_back(Edge());
    net[v].back().cost = co;
    net[v2].back().cost = -co;
    net[v].back().capacity = cap;
    net[v2].back().capacity = 0;
    net[v].back().from = v;
    net[v].back().to = v2;
    net[v2].back().from = v2;
    net[v2].back().to = v;
    net[v2].back().backEdgeIndex = (int)net[v].size() - 1;
    net[v].back().backEdgeIndex = (int)net[v2].size() - 1;
    net[v].back().flow = net[v2].back().flow = 0;
}

int main() {
    //std::ios_base::sync_with_stdio(false);

    map<pii, int> p;
    vector<pii> pp;

    int n;
    cin >> n;
    int a_, b_;
    cin >> a_ >> b_;

    double res = 0.0;
    vi x1(n),y1(n),x2(n),y2(n);
    for (int i = 0; i < n; ++i) {
        cin >> x1[i] >> y1[i];
        if (p.count(pii(x1[i], y1[i])) == 0) {
            int id = (int)p.size();
            p[pii(x1[i], y1[i])] = id;
            pp.push_back(pii(x1[i], y1[i]));
        }
        cin >> x2[i] >> y2[i];
        if (p.count(pii(x2[i], y2[i])) == 0) {
            int id = (int)p.size();
            p[pii(x2[i], y2[i])] = id;
            pp.push_back(pii(x2[i], y2[i]));
        }
        res += distC(x1[i], y1[i], x2[i], y2[i]);
    }
    for (int i = 0; i < n; ++i) {
    }
    assert(pp.size() == p.size());
    vi d(p.size());
    for (int i = 0; i < n; ++i) {
        d[p[pii(x1[i],y1[i])]] += 1;
        d[p[pii(x2[i],y2[i])]] -= 1;
    }


    assert((abs(accumulate(all(d), 0))  == 0));

    vi pos;
    vi neg;
    for (int i = 0; i < (int)p.size(); ++i) {
        /*for (int k = 0; k < n; ++k) {
            pos.push_back(i);
            neg.push_back(i);
        }*/
        if (d[i] > 0) {
                pos.push_back(i);
        }
        if (d[i] < 0) {
                neg.push_back(i);
        }
    }
    //assert(pos.size() == neg.size());

    vector<vector<Edge> > net(pos.size() + neg.size() + 2);
    int source = (int)pos.size() + (int)neg.size();
    int sink = source + 1;

    for (int i = 0; i < (int) neg.size(); ++i) {
        addEdge(net, (int)pos.size() + i, sink, -d[neg[i]], 0);
    }
    for (int i = 0; i < (int) pos.size(); ++i) {
        addEdge(net, source, i, d[pos[i]], 0.0);
        for (int j = 0; j < (int) neg.size(); ++j) {
            addEdge(net, i, (int)pos.size() + j, 1,
                    distC(
                        pp[pos[i]].first,
                        pp[pos[i]].second,
                        pp[neg[j]].first,
                        pp[neg[j]].second));

        }
    }
    debug("st");
    minCostMaxFlow(net, fordBelman, source, sink);
    res += cost(net);

/*
///

    pp.clear();
    pos.clear();
    neg.clear();

    for (int i = 0; i < 50; ++i) {
        pp.emplace_back(0, i);
    }
    for (int i = 0; i < 50; ++i) {
        pp.emplace_back(1, i);
    }
    for (int i = 0; i < 50; ++i) {
        pos.push_back(i);
        neg.push_back(49 - i);
    }



    vi o(pos.size());
    for (int i = 0; i < (int)o.size(); ++i) {
        o[i] = i;
    }
    random_shuffle(all(o));

    debug(o);

    bool ch = 0;
    do {
        ch = 0;
        for (int i = 0; i < (int)o.size(); ++i) {
            for (int j = 0; j < (int)o.size(); ++j) {
                if (i == j)
                    continue;
                int a = pos[i];  int A = neg[o[i]];
                int b = pos[j];  int B = neg[o[j]];
                if (dist(pp[a].first, pp[a].second, pp[A].first, pp[A].second) +
                        dist(pp[b].first, pp[b].second, pp[B].first, pp[B].second) >
                    dist(pp[a].first, pp[a].second, pp[B].first, pp[B].second) +
                        dist(pp[b].first, pp[b].second, pp[A].first, pp[A].second)) {

                    swap(o[i], o[j]);
                    ch = 1;
                }
            }
        }
        for (int i = 0; i < (int)o.size(); ++i) {
            assert(count(all(o), i) == 1);
        }
    } while(ch);

    debug(o);

    for (int i = 0; i < (int)o.size(); ++i) {
        int a = pos[i];  int A = neg[o[i]];
        res += dist(pp[a].first, pp[a].second, pp[A].first, pp[A].second);
    }*/
    printf("%0.18lf\n", (double)res);
    return 0;
}
