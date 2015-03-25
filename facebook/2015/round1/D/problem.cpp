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

/*void go(int v, int x, const vii& childs, const vii& dp, vector<pii>& minPositions) {
    int &res = dp[v][x];
    return res;
}*/

void dfs(int v, const vii& childs, vector<vector<ll>>& dp, vector<pii>& minPositions) {
    vector<ll> diff(dp[v].size());
    for (int v2: childs[v]) {
        dfs(v2, childs, dp, minPositions);
        if (minPositions[v2].first < diff.size()) {
            diff[minPositions[v2].first] += -dp[v2][minPositions[v2].first]
                + dp[v2][minPositions[v2].second];
        }
    }
    //debug(v);
    //debug(diff);

    ll sum = 0;
    for (int v2: childs[v]) {
        sum += dp[v2][minPositions[v2].first];
    }

    for (int x = 0; x < dp[v].size(); ++x) {
        ll &res = dp[v][x];
        res = sum + diff[x] + x + 1;
    }
    minPositions[v].first = (int)distance(dp[v].begin(),
            min_element(all(dp[v])));
    minPositions[v].second = -1;
    for (int i = 0; i < dp[v].size(); ++i) {
        if (i == minPositions[v].first)
            continue;
        if (minPositions[v].second == -1 ||
                dp[v][i] < dp[v][minPositions[v].second]) {
            minPositions[v].second = i;
        }
    }
    assert(minPositions[v].second != -1);
}

void solve() {
    int n;
    cin >> n;
    vii childs(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        //x = i;
        if (i) {
            childs[x - 1].push_back(i);
        }
    }
    vector<vector<ll>> dp(n);
    vector<pii> minPositions(n);
    for (int v = 0; v < n; ++v) {
        dp[v].assign(std::max(2, 1 + (int)childs[v].size()), INF);
    }
    dfs(0, childs, dp, minPositions);
    //debug(dp);
    //debug(minPositions);
    //cout << dp[0][2] << "\n";
    debug(minPositions[0]);
    assert(dp[0][minPositions[0].first] <= 3 * ((n + 1) / 2));
    cout << dp[0][minPositions[0].first] << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #" << t + 1 << ": ";
        solve();
    }

    return 0;
}
