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

int sign(ll x) {
    if (x > 0)
        return +1;
    if (x < 0)
        return -1;
    return 0;
}

ll det2(ll a, ll b, ll c, ll d) {
    return a * d - b * c;
}

ll area(ll x0, ll y0, ll x1, ll y1, ll x2, ll y2) {
    return det2(x0, y0, x1, y1) -
        det2(x0, y0, x2, y2) +
        det2(x1, y1, x2, y2);
}

int orient(int x0, int y0, int x1, int y1, int x2, int y2) {

    return sign(area(x0, y0, x1, y1, x2, y2));
}

bool isPointInside(int x, int y,
        int x0, int y0,
        int x1, int y1,
        int x2, int y2) {

    /*int s1 = orient(x, y, x0, y0, x1, y1);
    int s2 = orient(x, y, x1, y1, x2, y2);
    int s3 = orient(x, y, x2, y2, x0, y0);
    if ((s1 > 0 && s2 > 0 && s3 > 0) ||
            (s1 < 0 && s2 < 0 && s3 < 0)) {
        return 1;
    }
    return 0;*/

    return abs(area(x0, y0, x1, y1, x2, y2)) ==
        abs(area(x,y,x0,y0,x1,y1)) +
        abs(area(x,y,x1,y1,x2,y2)) +
        abs(area(x,y,x2,y2,x0,y0));
}

int main() {

    /*debug(isPointInside(0,0, 0,0,4,0,0,4));
    debug(isPointInside(1,1, 0,0,4,0,0,4));
    debug(isPointInside(1,0, 0,0,4,0,0,4));
    debug(isPointInside(0,1, 0,0,4,0,0,4));
    debug(isPointInside(0,-1, 0,0,4,0,0,4));
    debug(isPointInside(-1, 0, 0,0,4,0,0,4));
    return 0;*/

    std::ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    vector<int> y(n);
    for (int i =0 ; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    int X, Y;
    bool ok;
    do {
        ok = true;
        X = rand() % 10000;
        Y = rand() % 10000;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (orient(X, Y, x[i], y[i], x[j], y[j]) == 0)
                    ok = false;
            }
        }
    } while(!ok);
    vii countIn(n, vi(n));

    debug(X);
    debug(Y);
    vi badX(m);
    vi badY(m);
    for (int i = 0; i < m; ++i) {
        cin >> badX[i] >> badY[i];
    }

    for (int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for (int k = 0; k < m ;++k) {
                if (isPointInside(badX[k], badY[k], X, Y, x[i], y[i], x[j], y[j])) {
                    countIn[i][j] += orient(X, Y, x[i], y[i], x[j], y[j]);
                }
            }
        }
    }
    debug(countIn[0][1]);
    debug(countIn[1][4]);
    debug(countIn[4][0]);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                int c = countIn[i][j] + countIn[j][k] + countIn[k][i];
                if (c == 0) {
                    debug(i);
                    debug(j);
                    debug(k);
                    ++res;
                }
            }
        }
    }
    cout << res << "\n";
    return 0;
}
