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

void upd(int i, vi& ne, vi& pr) {
    int p = pr[i];
    int n = ne[i];

    if (p != -1)
        ne[p] = ne[i];
    if (n != -1)
        pr[n] = pr[i];
    pr[i] = ne[i] = -1;
}

int go(int o, vi nextX, vi prevX, vi nextY, vi prevY, const vi& d) {
    vi alive(nextX.size(), 1);
    int c = 0;
    while(o != -1) {
        assert(alive[o] == 1);
        alive[o] = 0;
        ++c;
        int O = o;
        if (d[o] == 0) {
            o = nextX[o];
        } else if (d[o] == 1) {
            o = nextY[o];
        } else if (d[o] == 2) {
            o = prevX[o];
        } else if (d[o] == 3) {
            o = prevY[o];
        }
        upd(O, nextX, prevX);
        upd(O, nextY, prevY);
    }
    return c;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vi x(n), y(n), d(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        char ch;
        cin >> ch;
        d[i] = (int)string(">^<v").find(ch);
    }

    vi nextX(n, -1);
    vi nextY(n, -1);
    vi prevX(n, -1);
    vi prevY(n, -1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (x[i] == x[j]) {
                if (y[j] < y[i]) {
                    if (prevY[i] == -1 || abs(y[j] - y[i]) < abs(y[i] - y[prevY[i]])) {
                        prevY[i] = j;
                    }
                }
                if (y[j] > y[i]) {
                    if (nextY[i] == -1 || abs(y[j] - y[i]) < abs(y[i] - y[nextY[i]])) {
                        nextY[i] = j;
                    }
                }
            }
            if (y[i] == y[j]) {
                if (x[j] < x[i]) {
                    if (prevX[i] == -1 || abs(x[j] - x[i]) < abs(x[i] - x[prevX[i]])) {
                        prevX[i] = j;
                    }
                }
                if (x[j] > x[i]) {
                    if (nextX[i] == -1 || abs(x[j] - x[i]) < abs(x[i] - x[nextX[i]])) {
                        nextX[i] = j;
                    }
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = max(res, go(i, nextX, prevX, nextY, prevY, d));
    }
    cout << res << "\n";

    return 0;
}
