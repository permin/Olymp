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
#include <valarray>

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
const long long LLINF = std::numeric_limits<ll>::max() / 4;

class DrivingPlans {
public:
    void dfs(int v, vi& comp, int c, const vii& al) {
        if (comp[v] != -1)
            return;
        comp[v] = c;
        for (int i = 0; i < al[v].size(); ++i) {
            dfs(al[v][i], comp, c, al);
        }
    }

    vector<ll> dijkstra(const vector<vector<pii>>& graph, int v) {
        vector<ll> dist(graph.size(), LLINF);
        dist[v] = 0;
        set<pair<ll, int>> Q;
        Q.insert(make_pair(0, v));
        while(!Q.empty()) {
            v = Q.begin()->second;
            Q.erase(Q.begin());
            for (int i = 0; i < graph[v].size(); ++i) {
                int v2 = graph[v][i].first;
                int d = graph[v][i].second;
                if (dist[v2] > dist[v] + d) {
                    Q.erase(make_pair(dist[v2], v2));
                    dist[v2] = dist[v] + d;
                    Q.insert(make_pair(dist[v2], v2));
                }
            }
        }
        return dist;
    }

    int add(int x, int y) {
        if (x == -1 || y == -1)
            return -1;
        x += y;
        static const int mod = 1e9+9;
        if (x >= mod)
            x -= mod;
        return x;
    }

    ll minDist;

    int solve(int source, int target, const vector<vector<pii>>& graph, const vector<ll>& from,
            const vector<ll>& to, const vi& sizes, vi& dp, vector<bool>& has) {
        int &res = dp[source];
        if (res != -2)
            return res;

        if (source == target) {
            has[source] = 1;
            if (sizes[source] > 1) {
                return res = -1;
            }
            return res = 1;
        }
        int sum = 0;
        for (int i = 0; i < graph[source].size(); ++i) {
            int v2 = graph[source][i].first;
            int d = graph[source][i].second;
            if (from[source] + to[v2] + d == minDist) {
                sum = add(sum, solve(v2, target, graph, from, to, sizes, dp, has));
                if (has[v2])
                    has[source] = 1;
            }
        }
        res = sum;
        if (has[source] && sizes[source] > 1) {
            res = -1;
        }
        return res;
    }

    int count(int n, vector <int> A, vector <int> B, vector <int> C) {
        vii al(n);
        for (int i = 0; i < A.size(); ++i) {
            if (C[i] == 0) {
                al[A[i] - 1].push_back(B[i] - 1);
                al[B[i] - 1].push_back(A[i] - 1);
            }
        }
        vector<int> comp(n, -1);
        int components = 0;
        for (int i = 0; i < n; ++i) {
            if (comp[i] == -1) {
                dfs(i, comp, components++, al);
            }
        }
        //debug(comp);
        vector<int> size(components, 0);
        for (int i = 0; i < comp.size(); ++i) {
            ++size[comp[i]];
        }
        {
            vector<vector<pii>> graph(components);
            for (int i = 0; i < A.size(); ++i) {
                int f = comp[A[i] - 1];
                int s = comp[B[i] - 1];
                if (f == s)
                    continue;
                graph[f].push_back(pii(s, C[i]));
                graph[s].push_back(pii(f, C[i]));
            }
            vector<ll> from = dijkstra(graph, 0);
            vector<ll> to = dijkstra(graph, comp[n-1]);
            minDist = from[comp[n-1]];
            debug(minDist)
            vector<int> dp(components, -2);
            vector<bool> has(components, false);
            return solve(comp[0], comp[n-1], graph, from, to, size, dp, has);
        }

    }
};

int main() {
    if (1) {
        vector<int> A;
        vector<int> B;
        vector<int> C;
        int mod = 1e9 + 9;
        int from, to;
        from = 3;
        to = 4;
        int free = 5;
        for (int i = 0; i < 32; ++i) {
            if (mod & (1 << i)) {
                int prev = from;
                for (int j = 0; j < i; ++j) {
                    int x = prev;
                    int y = ++free;
                    int z = j + 1 == i ? to : ++free;
                    A.push_back(x);
                    B.push_back(y);
                    C.push_back(1);

                    A.push_back(y);
                    B.push_back(z);
                    C.push_back(1);

                    A.push_back(x);
                    B.push_back(z);
                    C.push_back(2);

                    prev = z;
                }
            }
        }

        {
            A.push_back(1);
            B.push_back(2);
            C.push_back(10);

            A.push_back(2);
            B.push_back(3);
            C.push_back(10);

            int l = max(*max_element(all(A)), *max_element(all(B)));
            A.push_back(4);
            B.push_back(l + 1);
            C.push_back(10);

            cerr << l + 1 << "\n";
            for (int i = 0; i < A.size(); ++i) {
                cerr << A[i] << ",";
            }
            cerr << "\n";
            for (int i = 0; i < A.size(); ++i) {
                cerr << B[i] << ",";
            }
            cerr << "\n";
            for (int i = 0; i < A.size(); ++i) {
                cerr << C[i] << ",";
            }
            cerr << "\n";
            DrivingPlans D;
            debug(D.count(l + 1, A,B,C));
        }
        return 0;
    }

    DrivingPlans D;
    debug(D.count(
            4,
{1,1,2,3},
{2,3,4,4},
{1,1,1,1}));
    //debug(D.count(2,{1},{2},{0}));
    /*debug(D.count(5,{1,2,2,4,4},{2,3,5,1,5},{10,0,10,15,6})); // -1
    debug(D.count(5,{1,2,2,4,4},{2,3,5,1,5},{10,0,10,15,5})); // -1
    debug(D.count(5,{1,2,2,4,4},{2,3,5,1,5},{10,0,10,15,4})); // 1
    */
    return 0;
}
