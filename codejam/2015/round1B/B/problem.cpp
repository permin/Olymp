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

int p(int mask) {
    return (mask == 0) ? 0 : ((mask&1) + p(mask>>1));
}

int solve(int x, int y, int n) {
    int m = x * y;
    int res = INF;
    for (int mask = 0; mask < (1 << m); ++mask) {
        if (p(mask) == n) {
            int s = 0;
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    for (int dx = -1; dx <= +1; ++dx) {
                        for (int dy = -1; dy <= +1; ++dy) {
                            if ((dx == 0) ^ (dy == 0)) {
                                int ni = i + dx;
                                int nj = j + dy;
                                if (ni < 0 || ni >= x ||
                                        nj < 0 || nj >= y)
                                    continue;
                                int a = ni * y + nj;
                                int b = i * y + j;
                                if ((mask & (1 << a)) && (mask & (1<<b)))
                                    ++s;
                            }
                        }
                    }
                }
            }
            res = min(res, s);
        }
    }
    return res / 2;
}

int solve2(int x, int y, int n) {
    int c = (x * y + 1) / 2;
    if (c >= n)
        return 0;
    if (x > y)
        swap(x, y);
    int r = n - c;
    if (x == 1) {
        if (y & 1) {
            return 2 * r;
        } else {
            return 2 * r - 1;
        }
    }
        int res = 0;
        int corners = ((x*y)&1) ? 0 : 2;
        int c3 = (2 * x + 2 * y - 4 - corners);
        int tc = min(corners, r);
        r -= tc;
        res += tc * 2;
        int t3 = min(r, c3);
        r -= t3;
        res += t3 * 3;
        res += r * 4;
        return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    {
        for (int x = 1; x <= 20; ++x) {
            for (int y = 1; y * x <= 20; ++y) {
                for (int n = 0; n <= x * y; ++n) {
                    cerr << x << " " << y << " " << n << " " <<
                        solve(x,y,n) << " " << solve2(x,y,n) << "\n";
                    assert(solve2(x,y,n) == solve(x,y,n));
                }
            }
        }
    }
    size_t tests;
    cin >> tests;
    for (size_t t = 0; t < tests; ++t) {
        cout << "Case #" << t + 1 << ": ";
        int x, y, n;
        cin >> x >> y>> n;
        cout << solve(x,y,n) << "\n";
    }
    return 0;
}
