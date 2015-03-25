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
const int INF = std::numeric_limits<int>::max() / 2 - 4;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

int dx[] = {-1, 0, +1, 0};
int dy[] = {0, +1, 0, -1};
int direction(char ch) {
    if (ch == '^') return 0;
    if (ch == '>') return 1;
    if (ch == 'v') return 2;
    if (ch == '<') return 3;
    return -1;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> plan(n);
    for (int i = 0; i < n; ++i) {
        cin >> plan[i];
    }

    vector<vector<string>> maze(4, plan);
    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int dir = direction(plan[i][j]);
                if (dir == -1)
                    continue;
                dir += d;
                dir %= 4;
                int x = i;
                int y = j;

                while((0 <= x && x < n) &&
                      (0 <= y && y < m) && (
                      plan[x][y] == '.' ||
                      plan[x][y] == 'S' ||
                      plan[x][y] == 'G' ||
                      (x == i && y == j))) {
                    maze[d][x][y] = '#';
                    x += dx[dir];
                    y += dy[dir];
                }
            }
        }
    }

    viii dist(n, vii(m, vi(4, INF)));
    typedef std::tuple<int,int,int> State;
    queue<State> Q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (plan[i][j] == 'S') {
                Q.push(State(i, j, 1));
                dist[i][j][1] = 0;
            }
        }
    //debug(plan);
    //debug(maze);
    while(!Q.empty()) {
        int x,y,dir;
        std::tie(x,y,dir) = Q.front();
        Q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            int ndir = (dir + 1) % 4;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m ||
                    maze[dir][nx][ny] == '#') {
                continue;
            }
            if (dist[nx][ny][ndir] != INF) {
                continue;
            }
            assert(maze[dir][nx][ny] != '#');
            dist[nx][ny][ndir] = dist[x][y][dir] + 1;
            Q.push(State(nx, ny, ndir));
        }
    }
    int res = INF;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (plan[i][j] == 'G') {
                for (int d = 0; d < 4; ++d)
                    res = min(res, dist[i][j][d]);
            }
        }
    if (res == INF) {
        cout << "impossible\n";
    } else {
        cout << res << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<<t+1<<": ";
        solve();
    }
    return 0;
}
