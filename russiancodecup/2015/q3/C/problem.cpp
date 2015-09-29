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

int speed(int a, int b, bool day) {
    if (day)
        return a;
    return -b;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t-->0) {
        int a1,b1,a2,b2,z;
        cin >> a1 >> b1 >> a2 >> b2 >> z;

        int x1,x2;
        x1 = x2 = 0;

        double res = 0.0;
        for (int t = 0; t < z; ++t) {
            bool day = (t % 24) < 12;

            int y1 = x1 + speed(a1, b1, day);
            int y2 = x2 + speed(a2, b2, day);

            if (x1 == x2 && y1 == y2) {
                x1 = y1;
                x2 = y2;
                continue;
            }


            int dx = x1 - x2;
            int dy = y1 - y2;
            double cross = - 1.0 * dx / (dy - dx);

            if (x1 >= x2 && y1 >= y2) {
                res += 1.0;
            } else if (x1 >= x2 && y1 <= y2) {
                assert(0.0 <= cross && cross <= 1.0);
                res += cross;
            } else if (x1 <= x2 && y1 >= y2) {
                assert(0.0 <= cross && cross <= 1.0);
                res += 1.0 - cross;
            }
            x1 = y1;
            x2 = y2;
        }
        printf("%0.18lf\n", res);
    }
    return 0;
}
