/* Team: moscow04 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <deque>
#include <queue>
#include <string>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>

#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

#define DEBUG

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)((a).size()))
#define pb push_back
#define MP make_pair
#define mp MP

#ifdef DEBUG
    #define debug(x) cerr << #x << ": " << (x) << endl;
#else
    #define debug(x) ;
#endif

typedef pair<int, int> pii;
typedef long long ll;

template <typename T> T sqr (T x) {return x * x;}
template <typename T> T abs (T x) {return x > 0 ? x : -x;}

template <typename T>
ostream & operator << (ostream & out, vector<T> const & a) {
    out << "[";
    for (int i = 0; i < sz(a); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << a[i];
    }
    out << "]";
    return out;
}

template <typename T1, typename T2>
ostream & operator << (ostream & out, pair<T1, T2> const & p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

void showTime () {
#ifdef DEBUG
    static double prev;
    static bool first = true;

    double curr = (double)clock() / CLOCKS_PER_SEC;

    cerr.setf(ios::fixed);
    cerr.precision(3);
    cerr << "<";
    if (!first) {
        cerr << curr - prev << "sec, ";
    }
    cerr << curr << "sec>\n";

    first = false;
    prev = curr;
#endif
}

const ll LLINF = 1LL << 60;
const int INF = 1 << 30;

struct Edge {
    int from;
    int to;
    int capacity;
    int cost;
    int flow;
    int backEdgeIndex;
    void addFlow(int f) {
        assert(capacity >= f);
        capacity -= f;
        flow += f;
    }
};

vector<ll> fordBelman(int source, const vector<vector<Edge> >& net, vector<pii>& prev, const vector<ll>& ) {
    int vertices = net.size();
    vector<ll> dist(vertices, LLINF);
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
                ll newDist = dist[v] + e.cost;
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

vector<ll> dijkstra2(int source, const vector<vector<Edge> >& net, vector<pii>& prev, const vector<ll>& phi) {
    int vertices = net.size();
    vector<ll> dist(vertices, LLINF);
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
                ll newDist = phi[minAt] + dist[minAt] + e.cost - phi[v2];
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
    vector<ll> phi;
    {
        vector<pii> dummy;
        vector<ll> dummyPhi;
        phi = fordBelman(source, net, dummy, dummyPhi);
        //phi.assign(vertices, 0);
    }
    while (k) {
        vector<pii> prev;
        vector<ll> dist = finder(source, net, prev, phi);
        if (dist[sink] == LLINF)
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

long long cost(vector<vector<Edge> >& net) {
    ll res = 0;
    for (size_t i = 0; i < net.size(); ++i) {
        for (size_t j = 0; j < net[i].size(); ++j) {
            if (net[i][j].flow > 0) {
                res += 1LL * net[i][j].flow * net[i][j].cost;
            }
        }
    }
    return res;
}

void addEdge(vector<vector<Edge> >& net, int v, int v2, int cap, int co) {
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
    net[v2].back().backEdgeIndex = net[v].size() - 1;
    net[v].back().backEdgeIndex = net[v2].size() - 1;
    net[v].back().flow = net[v2].back().flow = 0;
}

int main () {
    //freopen("input.txt", "r", stdin);
    const int INF = 1e9;
    int n;
    cin >> n;
    vector<vector<int> > am(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i)
        am[i][i] = 0;
    vector<int> deg(n);
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        while (k --> 0) {
            int to, t;
            cin >> to >> t;
            --to;
            --deg[i];
            ++deg[to];
            am[i][to] = min(am[i][to], t);
            res += t;
        }
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                am[i][j] = min(am[i][j], am[i][k] + am[k][j]);
            }
    int source = n;
    int sink = n + 1;
    vector<vector<Edge> > net(n + 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            if ((i == 0 || deg[i] > 0) && deg[j] < 0) {
                addEdge(net, i, j, INF, am[i][j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i == 0 || deg[i] > 0) {
            addEdge(net, source, i, i ? deg[i] : INF, 0);
        } else {
            addEdge(net, i, sink, -deg[i], 0);
        }
    }
    minCostMaxFlow(net, dijkstra2, source, sink);
    res += cost(net);
    cout << res << "\n";


    return 0;
}
