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

const int maxN = 1601;
double am[maxN][maxN];
double dist[maxN];
int pre[maxN];
bool alive[maxN];
int n;


double sqr(int x) {
    return 1.0 * x * x;
}

void solve(int source, int sink, vi& path, double& res) {
    for (int i = 0; i < n; ++i) {
        dist[i] = 10000 * 2 * 2;
        alive[i] = 1;
    }
    dist[source] = 0;

    for (int i = 0; i < n; ++i) {
        int closest = -1;
        for (int v = 0; v < n; ++v) {
            if (!alive[v])
                continue;
            if (closest == -1 || dist[closest] > dist[v])
                closest = v;
        }
        if (closest == sink)
            break;
        alive[closest] = 0;
        for (int v2 = 0; v2 < n; ++v2) {
            if (dist[v2] >  dist[closest] + am[closest][v2]) {
                pre[v2] = closest;
                dist[v2] = min(dist[v2], dist[closest] + am[closest][v2]);
            }
        }
    }
    res += dist[sink];
    vi a;
    while(sink != source) {
        a.push_back(sink);
        sink = pre[sink];
    }
    reverse(all(a));
    for (size_t i = 0; i < a.size(); ++i)
        path.push_back(a[i]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int m,k,v_r, v_f;
    cin >> n >> m >> k >> v_r >> v_f;
    vi x(n);
    vi y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            am[i][j] = sqrt(sqr(x[i]-x[j]) + sqr(y[i] - y[j])) / v_f;
        }
    }

    for (int i = 0; i < m; ++i) {
        int a,b;
        cin >> a >> b;
        --a;
        --b;
        am[a][b] = min(am[a][b], sqrt(sqr(x[a]-x[b]) + sqr(y[a] - y[b])) / v_r);
        am[b][a] = am[a][b];
    }

    double res = 0;
    vi path(1,0);
    int p = 0;
    for (int i = 0; i < k; ++i) {
        int a;
        cin >> a;
        --a;
        solve(p, a, path, res);
        p = a;
    }
    solve(p, n-1, path, res);
    std::cout.precision(18);
    cout << res << "\n";
    for (int x: path) {
        cout << x + 1 << " ";
    }
    cout << "\n";


    return 0;
}
