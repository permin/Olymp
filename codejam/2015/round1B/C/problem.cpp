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

int solve() {
    int n;
    cin >> n;
    std::vector<int> d;
    std::vector<int> m;
    for (int i = 0; i < n; ++i) {
        // d h m
        int x,y,z;
        cin >> x >> y >> z;
        for (int j = 0; j < y; ++j) {
            d.push_back(x);
            m.push_back(z+j);
        }
    }
    if (m.size() > 2)
        return INF;
    assert(m.size() <= 2);
    if (m.size() == 1) {
        return 0;
    }
    ll d1 = d[0];
    ll d2 = d[1];
    ll m1 = m[0];
    ll m2 = m[1];

    if (m1 == m2) {
        return 0;
    }

    if (d2 < d1) {
        swap(d1,d2);
        swap(m1, m2);
    }

    if (d1 == d2) {
        // 1 is faster
        if (m1 > m2)
            swap(m1, m2);
        if (m1 * 360 <= (360 - d1) * (m2-m1)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        // d1 < d2
            ll delta = d2 - d1;
        if (m1 < m2) {
            ll left =  m1 * (delta + 360);
            ll right = (m2 - m1) * (360 - d2);
            return left > right;
        } else {
            ll left = (360 - delta) * m2;
            ll right = (360 - d1) * (m1 - m2);
            return left > right;

        }
    }
    return INF;

}

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t tests;
    cin >> tests;
    for (size_t t = 0; t < tests; ++t) {
        cout << "Case #" << t + 1 << ": ";
        cout << solve() << "\n";
    }
    return 0;
}
