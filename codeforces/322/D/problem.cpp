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

int main() {
    std::ios_base::sync_with_stdio(false);

    int dx1, dx2, dx3, dy1, dy2, dy3;
    char l1, l2, l3;
    cin >> dx1 >> dy1;
    cin >> dx2 >> dy2;
    cin >> dx3 >> dy3;
    l1 = 'A';
    l2 = 'B';
    l3 = 'C';

    for (int it = 0; it < 500000; ++it) {
        if (rand() & 1) {
            swap(l1, l2);
            swap(dx1, dx2);
            swap(dy1, dy2);
        }
        if (rand() & 1) {
            swap(l3, l2);
            swap(dx3, dx2);
            swap(dy3, dy2);
        }
        if (rand() & 1) {
            swap(l1, l3);
            swap(dx1, dx3);
            swap(dy1, dy3);
        }
        if (rand() & 1) {
            swap(dx1, dy1);
        }
        if (rand() & 1) {
            swap(dx2, dy2);
        }
        if (rand() & 1) {
            swap(dx3, dy3);
        }
        int x1, y1, x2,y2,x3,y3;
        int side = -1;
        {
            int d = dy1;
            if (dx2 == dx3 && dx2 + dx1 == d && dy2 + dy3 == d) {
                side = d;
                x1 = y1 = 0;
                x3 = x2 = dx1;
                y2 = 0;
                y3 = dy2;
            }
        }
        {
            int d = dy1;
            if (dy2 == d && dy3 == d && dx1 + dx2 + dx3 == d) {
                side = d;
                x1=y1=y2=y3=0;
                x2=dx1;
                x3=dx1+dx2;
            }
        }
        if (side >= 0) {
            vector<string> plan(side, string(side, '?'));
            for (int x = x1; x < x1 + dx1; ++x) {
                for (int y = y1; y < y1 + dy1; ++y) {
                    plan[x][y] = l1;
                }
            }
            for (int x = x2; x < x2 + dx2; ++x) {
                for (int y = y2; y < y2 + dy2; ++y) {
                    plan[x][y] = l2;
                }
            }
            for (int x = x3; x < x3 + dx3; ++x) {
                for (int y = y3; y < y3 + dy3; ++y) {
                    plan[x][y] = l3;
                }
            }
            cout << side << "\n";
            for (int i = 0; i < side; ++i) {
                cout << plan[i] << "\n";
            }
            exit(0);
        }
    }
    cout << "-1\n";

    return 0;
}
