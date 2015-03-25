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
const long long LLINF = 30000 + 0 * std::numeric_limits<ll>::max() / 3;

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

struct Edge {
    int source;
    int target;
    ll weight;
};

void read(Edge* e) {
    cin >> e->source >> e->target >> e->weight;
    --e->target;
    --e->source;
}

Edge rev(Edge e) {
    swap(e.target,e.source);
    return e;
}

void dfs(int v, const vector<vector<Edge>>& al, vector<bool>& used) {
    if (used[v])
        return;
    used[v] = true;
    for (const auto& e: al[v]) {
        dfs(e.target, al, used);
    }
}

vector<ll> fordBellman2(int s, const vector<vector<Edge>>& al, vi& prev) {
    int vertices = (int)al.size();
    vector<ll> distances(vertices, LLINF);
    distances[s] = 0;
    vector<int> lastUpdate(vertices);
    for (int it = 0; it < vertices; ++it) {
        for (int v = 0; v < al.size(); ++v) {
            for (const auto& e: al[v]) {
                int v2 = e.target;
                ll c = e.weight;
                if (distances[v] != LLINF && distances[v2] > distances[v] + c) {
                    prev[v2] = v;
                    distances[v2] =
                            distances[v] + c;
                    lastUpdate[v2] = it;
                }
            }
        }
    }
    vector<bool> used(vertices);
    for (int v = 0; v < vertices; ++v) {
        if (lastUpdate[v] > vertices - 1 || distances[v] <= -LLINF) {
            dfs(v, al, used);
            distances[v] = -LLINF;
        }
    }
    for (int i = 0; i < used.size(); ++i) {
        if (used[i]) {
            distances[i] = -LLINF;
        }
    }
    return distances;
}

vector<ll> fordBellman(int s, const vector<vector<Edge>>& al, vi& prev) {
    int vertices = (int)al.size();
    vector<ll> distances(vertices, LLINF);
    distances[s] = 0;
    vi insertensInQueue(vertices);
    vector<bool> inQueue(vertices);
    queue<int> Q;
    auto push = [&](int v) {
        if (inQueue[v]) return;
        if (insertensInQueue[v] == 1 + vertices) return;
        ++insertensInQueue[v];
        inQueue[v] = true;
        Q.push(v);
    };
    auto pop = [&] ()->int {
        int r = Q.front();
        Q.pop();
        inQueue[r] = false;
        return r;
    };
    push(s);
    while(!Q.empty()) {
        int v = pop();
        for (const Edge& e: al[v]) {
            int v2 = e.target;
            if (distances[v2] > distances[v] + e.weight) {
                distances[v2] = distances[v] + e.weight;
                push(v2);
                prev[v2] = v;
            }
        }
    }
    vector<bool> used(vertices);
    for (int i = 0; i < vertices; ++i) {
        if (insertensInQueue[i] == 1 + vertices) {
            dfs(i, al, used);
        }
    }
    for (int i = 0; i < used.size(); ++i) {
        if (used[i]) {
            distances[i] = -LLINF;
        }
    }
    return distances;
}

template<class C>
void dfs2(int v, const C& al, vector<bool> & used) {
    if (used[v])
        return;
    used[v] = true;
    for (int v2: al[v]) {
        dfs2(v2, al, used);
    }
}

vector<ll> tarjan(int s, const vector<vector<Edge>>& al, vi& prev) {
    int vertices = (int)al.size();
    vector<ll> distances(vertices, LLINF);
    distances[s] = 0;
    vi insertensInQueue(vertices);
    vector<bool> inQueue(vertices);
    queue<int> Q;

    vector<std::list<int>::iterator> where(vertices);
    vector<std::list<int>> childs(vertices);
    vector<bool> skip(vertices);

    auto push = [&](int v) {
        skip[v] = false;
        if (inQueue[v]) return;
        if (insertensInQueue[v] == 1 + vertices) return;
        ++insertensInQueue[v];
        inQueue[v] = true;
        Q.push(v);
    };
    auto pop = [&] ()->int {
        int r = Q.front();
        Q.pop();
        inQueue[r] = false;
        return r;
    };
    push(s);
    while(!Q.empty()) {
        int v = pop();
        if (skip[v])
            continue;
        for (const Edge& e: al[v]) {
            int v2 = e.target;
            if (distances[v2] > distances[v] + e.weight) {
                distances[v2] = distances[v] + e.weight;
                dfs2(v2, childs, skip);
                push(v2);

                if (prev[v2] != -1) {
                    int p = prev[v2];
                    childs[p].erase(where[v2]);
                }

                prev[v2] = v;
                where[v2] = childs[v].insert(childs[v].begin(), v2);
            }
        }
    }
    vector<bool> used(vertices);
    for (int i = 0; i < vertices; ++i) {
        if (insertensInQueue[i] == 1 + vertices || distances[i] < -LLINF) {
            dfs(i, al, used);
        }
    }
    for (int i = 0; i < used.size(); ++i) {
        if (used[i]) {
            distances[i] = -LLINF;
        }
    }
    return distances;
}


int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL_RUN
    //freopen("path.in", "r", stdin);
    //freopen("path.out", "w", stdout);
#endif
    int n, m, s;
    cin >> n >> m;
    s = 0;
    vector<vector<Edge>> al(n);
    for (int i = 0; i < m; ++i) {
        Edge e;
        read(&e);
        al[e.source].push_back(e);
        //al[e.target].push_back(rev(e));
    }

    /*vector<ll> distances = fordBellman(s, al);
    vector<ll> distances2 = fordBellman2(s, al);
    for (int i = 0; i < n; ++i) {
        if (distances[i] != distances2[i]) {
            debug(i);
            debug(-LLINF);
            debug(distances[i]);
            debug(distances2[i]);
            assert(distances2[i] >= -1000LL * 1000 * 1000 * 1000 * 1000 * n);
            assert(distances2[i] >= -LLINF);
            assert(
                distances[i] == distances2[i]);
        }
    }*/
    vi prev(n, -1);
    //auto distances = tarjan(s, al, prev);
    auto distances = tarjan(s, al, prev);
    //assert(distances==vector<ll>({0,10,11,LLINF}));
    for (int i = 0; i < n; ++i) {
        ll x = distances[i];
        if (x >= LLINF)
            x = 30000;
        cout << (i>0?" ":"") << x;
    }
    /*for (ll x: distances) {
        if (x >= LLINF)
            cout << 30000 << " ";
        else
            cout << x << " ";
    }*/
    cout << "\n";
    /*if (distances[n-1] == LLINF) {
        cout << "-1\n";
    } else {
        vi p;
        int x = n - 1;
        while(x != -1) {
            p.push_back(x);
            x = prev[x];
        }
        for (int i = 0; i < p.size(); ++i) {
            cout << p[p.size() - 1 - i] + 1 << " ";
        }
        return 0;
    }*/
    /*for (ll x: distances) {
        if (x >= LLINF) {
            cout << "*";
        } else if (x <= -LLINF) {
            cout << "-";
        } else {
            cout << x;
        }
        cout << "\n";
    }*/
    return 0;
}

