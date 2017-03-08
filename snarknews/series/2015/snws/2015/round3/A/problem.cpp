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

int solve(int i, int j, vii& dp) {
    int n = int(dp.size());
    assert(i != j);
    int & res = dp[i][j];
    if (res >= 0)
        return res;
    res = -1;
    set<int> Q;
    assert(0 <= i && i < n);
    assert(0 <= j && j < n);
    int dx = (j - i) / abs(j - i);
    assert(dx == -1 || dx == +1);
    if (i == 0 && dx == +1 && i + 1 != j && i + 2 != j && i + 2 < n) {
        Q.insert(solve(j, i + 2, dp));
        //Q.insert(solve(n-1-j, n-1-i - 2, dp));
        //std::cerr << i << " " << j << " -> " << j << " " << i + 2 << ":" << Q << "\n";
    }
    if (i == n - 1 && dx == -1 && i - 1 != j && i - 2 != j && i - 2 >= 0) {
        Q.insert(solve(j, i - 2, dp));
        //Q.insert(solve(n - 1 - j, n - 1 - i + 2, dp));
        //std::cerr << i << " " << j << " -> " << j << " " << i - 2 << ":" << Q << "\n";
    }
    int ni = i + dx;
    assert(abs(i-j) > abs(ni-j));
    if (ni != j && 0 <= ni && ni < n) {
        Q.insert(solve(j, i + dx, dp));
        //Q.insert(solve(n-1-j, n-1-ni, dp));
        //std::cerr << i << " " << j << " -> " << j << " " << i + dx << ":" << Q << "\n";
    }
    res = 0;
    while(Q.count(res)) {
        ++res;
    }
    assert(res <= 5);
    assert(res >= 0);
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t-->0) {
        int n, m;
        cin >> n >> m;
        //vector<viii> dp(n, viii(n, vii(2, vi(2, -1))));
        vii dp(n, vi(n, -1));
        vector<string> plan(n);
        int x = 0;
        for (int i = 0; i < n; ++i) {
            cin >> plan[i];
        }
        for (int i = 0; i < m; ++i) {
            int b, w;
            b = w = -1;
            std::string s;
            for (int j = 0; j < n; ++j) {
                if (plan[j][i] == 'B')
                    b = j;
                if (plan[j][i] == 'W')
                    w = j;
                s += plan[j][i];
            }
            assert(b != -1 && w != -1);
            assert(b < w);
            x = x ^ solve(w, b, dp);
            std::cerr << "---\n";
            //debug(w);
            //debug(b);
            debug(i);
            debug(s);
            debug(solve(w,b,dp));
        }
        if (x == 0) {
            cout << "Black\n";
        } else {
            cout << "White\n";
        }
    }

    return 0;
}
