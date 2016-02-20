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
const int INF = std::numeric_limits<int>::max() / 3;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

bool ok(int i, int j, const vector<string>& plan) {
    return i >= 0 && j >= 0 && i < (int)plan.size() &&
        j < (int)plan[0].size() && plan[i][j] != '#';
}

vector<vector<int>> bfs(char ch, const vector<string>& plan) {
    queue<pii> Q;

    int n = (int)plan.size();
    int m = (int)plan[0].size();
    vii dist(n,vi(m, INF));
    for (int i = 0 ;i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (plan[i][j] == ch) {
                Q.push(pii(i, j));
                dist[i][j] = 0;
            }
        }
    }
    while(!Q.empty()) {
        pii v = Q.front();
        Q.pop();
        for (int dx = -1; dx <= +1; ++dx)
            for (int dy = -1; dy <= +1; ++dy) {
                if (abs(dx) + abs(dy) == 1) {
                    int ni = v.first + dx;
                    int nj = v.second + dy;
                    if (ok(ni, nj, plan)) {
                        if (dist[ni][nj] == INF) {
                            dist[ni][nj] = dist[v.first][v.second] + 1;
                            Q.push(pii(ni,nj));
                        }
                    }
                }
            }
    }
    return dist;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> plan(n, string(m,'?'));
    for (int i = 0; i < n; ++i)
        cin >> plan[i];

    vii f=bfs('1', plan);
    vii s=bfs('2', plan);
    vii t=bfs('3', plan);

    int res = INF;
    int d12 = INF;
    int d13 = INF;
    int d23 = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (plan[i][j] == '1') {
                d12 = min(d12, s[i][j]);
                d13 = min(d13, t[i][j]);
            }
            if (plan[i][j] == '2') {
                d12 = min(d12, f[i][j]);
                d23 = min(d23, t[i][j]);
            }
            if (plan[i][j] == '3') {
                d13 = min(d13, f[i][j]);
                d23 = min(d23, s[i][j]);
            }
            res = min(res, -2 + f[i][j] + s[i][j] + t[i][j]);
        }
    }
    res = min(res, -2+ d12 + d13);
    res = min(res, -2+ d13 + d23);
    res = min(res, -2+ d12 + d23);
    if (res >= INF - 23) {
        res = -1;
    }
    cout << res << "\n";

    return 0;
}
