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

const int N = 100*1000 + 5;
const int M = 17;
int dp[N][M];
vi mins[N][M];

int timeIn[N];
int timeOut[N];
int t;

void dfs(int v, int p, const vii& al, vii& childs) {
    ++t;
    dp[v][0] = p;
    timeIn[v] = t;
    for (int v2: al[v]) {
        if (v2 != p) {
            childs[v].push_back(v2);
            dfs(v2, v, al, childs);
        }
    }
    ++t;
    timeOut[v] = t;
}

void sh(vi& x, size_t s = 10) {
    if (x.size() >= s) {
        x.resize(s);
    }
    //x.shrink_to_fit();
}

bool isPar(int par, int ch) {
    return timeIn[par] <= timeIn[ch] && timeIn[ch] <= timeOut[par];
}

void me(const vi& x, const vi& y, vi& z) {
    std::merge(all(x), all(y), std::back_inserter(z));
    sh(z);
}

void add(const vi& x, vi& z) {
    vi ans;
    me(x,z,ans);
    sh(ans);
    z = ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vii al(n);
    for (int i = 0; i < n - 1; ++i) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        al[x].push_back(y);
        al[y].push_back(x);
    }
    vi c(m);
    for (int i = 0; i < m; ++i) {
        cin >> c[i];
        --c[i];
    }

    vii childs(n);
    dfs(0, 0, al, childs);

    for (int i = 0; i < m; ++i) {
        mins[c[i]][0].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        sort(all(mins[i][0]));
        sh(mins[i][0]);
    }
    for (int L = 1; L < M; ++L) {
        for (int v = 0; v < n; ++v) {
            int v2 = dp[v][L-1];
            dp[v][L] = dp[v2][L-1];
            me(mins[v][L-1],
                    mins[v2][L-1], mins[v][L]);
        }
    }

    while(q-->0) {
        int x,y,a;
        cin >> x >> y >> a;
        --x;--y;
        vi ans;
        //debug(x);
        //debug(y);
        int oldX = x;
        for (int i = M-1; i >= 0; --i) {
            int X = dp[x][i];
            if (!isPar(X, y)) {
                add(mins[x][i], ans);
                x = X;
            }
        }
        if (!isPar(x, y)) {
            //debug(dp[x][0]);
            add(mins[x][0], ans);
        } else {
            //debug(x);
        }
        x = oldX;
        for (int i = M-1; i >= 0; --i) {
            int Y = dp[y][i];
            if (!isPar(Y, x)) {
                add(mins[y][i], ans);
                y = Y;
            }
        }
        if (!isPar(y, x)) {
            //debug(dp[y][0]);
            add(mins[y][1], ans);
        } else {
            add(mins[y][0], ans);
            //debug(y);
        }
        sh(ans, a);
        cout << ans.size() << " ";
        for (int z: ans) {
            cout << z + 1<< " ";
        }
        cout << "\n";
    }


    return 0;
}
