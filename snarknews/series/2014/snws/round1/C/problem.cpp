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
#include <unordered_map>
#include <functional>
#include <bitset>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

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
const long long LLINF = std::numeric_limits<ll>::max() / 3;

int main() {
    int n,m,s;
    cin >> n >> m >> s;
    vector<vector<pii>> al(n);
    for (int i = 0; i < m; ++i) {
        int a,b,t;
        cin >> a >> b >> t;
        --a;--b;
        al[a].push_back(pii(b, t));
        al[b].push_back(pii(a, t));
    }
    vector<int> g(s);
    for (int i = 0; i < s; ++i) {
        cin >> g[i];
        --g[i];
    }
    int source;
    int target = 0;
    cin >> source;
    --source;

    vector<ll> distGuards(n, LLINF);
    {
        set<pair<ll, int>> Q;
        for (int x: g) {
            distGuards[x] = 0;
            Q.insert(make_pair(0, x));
        }
        while(!Q.empty()) {
            int y = Q.begin()->second;
            Q.erase(Q.begin());
            for (int i = 0; i < al[y].size(); ++i) {
                ll ndist = distGuards[y] + al[y][i].second;
                int v2 = al[y][i].first;
                if (ndist < distGuards[v2]) {
                    Q.erase(make_pair(distGuards[v2], v2));
                    distGuards[v2] = ndist;
                    Q.insert(make_pair(distGuards[v2], v2));
                }
            }
        }
    }

    vector<ll> dist(n, LLINF);
    set<pair<ll, int>> Q;
    if (distGuards[source] != 0) {
        dist[source] = 0;
        Q.insert(make_pair(0, source));
    }
    while (!Q.empty()) {
        int v = Q.begin()->second;
        Q.erase(Q.begin());
        for (int i = 0; i < al[v].size(); ++i) {
            int v2 = al[v][i].first;
            ll ndist = dist[v] + al[v][i].second;
            if (ndist >= distGuards[v2]) {
                continue;
            }
            if (ndist < dist[v2]) {
                Q.erase(make_pair(dist[v2], v2));
                dist[v2] = ndist;
                Q.insert(make_pair(dist[v2], v2));
            }
        }
    }
    if (dist[target] < LLINF) {
        cout << dist[target];
    } else {
        cout << "-1";
    }
    cout << "\n";


    return 0;
}
