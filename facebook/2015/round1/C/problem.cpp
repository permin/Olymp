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

struct BoundedScore {
    BoundedScore(size_t my, size_t opponent):
        my(my), opponent(opponent) {}
    bool operator()(size_t x, size_t y) const {
        return x <= my && y <= opponent;
    }
    size_t my, opponent;
};

struct IsStressFree {
    IsStressFree(size_t my, size_t opponent):
        my(my), opponent(opponent), boundedScore(my, opponent) {}
    bool operator()(size_t x, size_t y) const {
        return boundedScore(x,y) && (
                (x == 0 && y == 0) || (x > y));
    }
    size_t my, opponent;
    BoundedScore boundedScore;
};

struct IsStressfull {
    IsStressfull(size_t my, size_t opponent):
        my(my), opponent(opponent), boundedScore(my, opponent) {}
    bool operator()(size_t x, size_t y) const {
        return boundedScore(x,y) && (
                (x <= y) || (x > y && y == opponent));
    }
    size_t my, opponent;
    BoundedScore boundedScore;
};

const int MOD = 1000000007;

int add(size_t x, size_t y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
    return int(x);
}

/*size_t mul(size_t x, size_t y) {
    ll res = x * y;
    return res % MOD;
}*/

template<class F>
size_t countNumberOfWays(size_t x, size_t y, vii& dp, F isValid) {
    int& res = dp[x][y];
    if (res >= 0)
        return res;
    res = 0;

    for (size_t dx: {0, 1}) {
        for (size_t dy: {0, 1}) {
            if (dx + dy == 1) {
                if (isValid(x + dx, y + dy))
                    res = add(res, countNumberOfWays(x + dx, y + dy, dp, isValid));
            }
        }
    }

    if (res == 0)
        ++res;

    return res;
}

void solve() {
    string s;
    cin >> s;
    int my, opponent;
    sscanf(s.c_str(), "%d-%d", &my, &opponent);
    for (int i = 0; i < 2; ++i) {
        vii pd(my + 1, vi(opponent + 1, -1));
        if (i == 0)
            cout << countNumberOfWays(0, 0, pd, IsStressFree(my, opponent)) << " ";
        if (i == 1)
            cout << countNumberOfWays(0, 0, pd, IsStressfull(my, opponent)) << "\n";
    }
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
