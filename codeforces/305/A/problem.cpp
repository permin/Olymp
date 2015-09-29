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

int m;

struct D {
    ll x, y, h, a;
};

void read(D& d) {
    cin >> d.h >> d.a >> d.x >> d.y;
}

pii solve(D d) {
    int a1, a2;
    a1 = a2 = -1;
    for (int i = 0; i < m + m + m; ++i) {
        if (d.h == d.a) {
            if (a1 == -1) {
                a1 = i;
            } else if (a2 == -1) {
                assert(a1 != -1);
                a2 = i;
                break;
            } else {
                break;
            }
        }
        d.h = (d.x * d.h + d.y) % m;
    }
    if (a1 == -1) {
        return pii(-1,-1);
    }
    if (a2 == -1) {
        return pii(a1, 0);
    }
    assert(a1 != a2);
    return pii(a1, a2 - a1);
}

int gcdex(int a, int b, int& x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int xx,yy;
    int aa, bb;
    aa = b % a;
    bb = a;
    int d = gcdex(aa, bb, xx, yy);
    x = yy - (b/a) * xx;
    y = xx;
    return d;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    D d1,d2;
    cin >> m;
    read(d1);
    read(d2);
    auto a1 = solve(d1);
    auto a2 = solve(d2);
    debug(a1);
    debug(a2);
    if (a1.first == -1 || a2.first == -1) {
        cout << "-1\n";
        return 0;
    }
    if (a1.second == a2.second) {
        if (a1.first == a2.first) {
            cout << a1.first << "\n";
        } else {
            cout << "-1\n";
        }
        return 0;
    }
    {
        if (x >= 0 && a1.first + x * a1.second == a2.first + x * a2.second) {
            cout << a1.first + x * a1.second  << "\n";
            return 0;
        }
        cout << "-1\n";
    }

    return 0;
}
