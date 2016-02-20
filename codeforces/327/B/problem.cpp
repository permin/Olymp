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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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

double sqr(double x) {
    return x * x;
}

double dist(pdd A, pdd B) {
    return sqrt(sqr(A.first- B.first) + sqr(A.second-B.second));
}

pdd conv( pdd A, pdd B, double t) {
    return pdd(A.first * t + (1-t) * B.first,
        A.second * t + (1-t) * B.second);
}

pdd add(pdd A, pdd B, double m) {
    return pdd(A.first + B.first * m,
        A.second + B.second * m);
}

double dist(pdd O, pdd A, pdd B) {
    double L = 0;
    double U = 1.0;
    for (int it = 0; it < 10000; ++it) {
        double t1 = L + 1.0 /3 * (U -L);
        double t2 = L + 2.0 /3 * (U -L);
        auto C1 = conv(A, B, t1);
        auto C2 = conv(A, B, t2);
        if (dist(O, C1) > dist(O, C2)) {
            L = t1;
        } else {
            U = t2;
        }
    }
    return dist(O, conv(A, B, 0.5 * (L+U)));
}

int main() {
    pdd O, T;
    cin >> O.first >> O.second;
    cin >> T.first >> T.second;
    T = add(T, O, -1);
    O = add(O, O, -1);
    double v, t;
    cin >> v >> t;
    pdd v1, v2;
    cin >> v1.first >> v1.second;
    cin >> v2.first >> v2.second;

    ///pdd A = T;
    pdd B = add(T, pdd(-v1.first, -v1.second), t);
    //pdd C = add(B, pdd(-v2.first, -v2.second), 1e7);
    double lower = 0.0;
    double upper = 1e8;
    for (int it = 0; it < 1000; ++it) {
        double m = (lower + upper)/2;
        pdd G;
        if (m < t) {
            G =  add(T, pdd(-v1.first, -v1.second), m);
        } else {
            G =  add(B, pdd(-v2.first, -v2.second), m - t);
        }
        double ti = dist(O, G) / v;
        if (ti < m) {
            upper = m;
        } else {
            lower = m;
        }
    }
    debug(lower)
    debug(upper)
    printf("%0.18lf\n", lower);
    return 0;
}
