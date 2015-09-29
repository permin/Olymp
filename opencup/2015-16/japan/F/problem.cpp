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

const int N = 201;
const int P = 1001;
double dp[N][P];
bool calc[N][P];
double maxCost[N];

struct Edge {
    int len;
    double cost;
    int target;
};

vector<vector<Edge>> al;

double solve(int v, int p) {
    if (p == 0) {
        if (v == 0) {
            return 0.0;
        } else {
            return (double)-INF;
        }
    }
    double& res = dp[v][p];
    if (calc[v][p])
        return res;
    res = (double)-INF;

    res = max(res, solve(v, p - 1) + maxCost[v]);
    for (const auto& e: al[v]) {
        if (e.len <= p) {
            res = max(res, solve(e.target, p - e.len) +
                    e.len * e.cost);
        }
    }
    calc[v][p] = 1;
    return res;
}

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    al.resize(n);
    for (int i = 0 ;i < m; ++i) {
        Edge e;
        int x,y,z,t;
        cin >> x >> y >> z >> t;
        --x,--y;
        e.len = z;
        e.cost = 1.0 * t / z;
        e.target = y;
        al[x].push_back(e);

        e.target = x;
        al[y].push_back(e);
    }

    for (int i = 0; i < n; ++i) {
        for (const auto& e: al[i]) {
            maxCost[i] = max(maxCost[i], e.cost);
        }
    }

    printf("%0.18lf\n", solve(0, p));
    return 0;
}
