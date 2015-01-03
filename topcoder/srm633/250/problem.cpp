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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

class PeriodicJumping{
public:
    int minimalTime(int x, vector <int> l) {
        if (x < 0)
            x = -x;
        ll sum = 0;
        for (int i = 0; i < l.size(); ++i)
            sum += l[i];
        int r = 0;
        if (x > sum) {
            r = x / sum;
            x -= sum * r;
            for (int i = 0; i <= l.size(); ++i) {
                if (x <= 0) {
                    return r * l.size() + i;
                }
                x -= l[i];
            }
        }
        if (x == 0)
            return r * l.size();
        ll a = l[0];
        ll b = l[0];
        for (int i = 1; ; ++i) {
            if (a <= x && x <= b) {
                return r * l.size() + i;
            }
            int j = i % l.size();
            int c = l[j];
            if (a <= c && c <= b) {
                a = 0;
            } else if (c < a) {
                a = abs(a - c);
            } else {
                a = abs(b - c);
            }
            b = b + c;
        }
        return -1;
    }
};

int main() {
    PeriodicJumping A;
    assert(A.minimalTime(
        1000000000, {16769023}) == 60);
    assert(A.minimalTime(15, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 5);
    assert(A.minimalTime(5, {5}) == 1);
    assert(A.minimalTime(	1, {10}) == 2);
    assert(A.minimalTime(	-10, {2, 3, 4, 500, 6, 7, 8}		) == 11);
    assert(A.minimalTime(	0, {19911120}) == 0);
    assert(A.minimalTime(	-8, {1}) == 8);
    assert(A.minimalTime(-1000000000, {1}) == 1000000000);
    assert(A.minimalTime(	4, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 4);
    assert(A.minimalTime(
                -1, {36762, 597343, 628698, 87034, 509806, 482319, 731876, 558939, 482321, 260758, 613440, 313289, 874772, 424528, 30857, 799869, 458065, 592571, 134480, 486268, 774339, 251412, 323207, 353747, 733279}
                ) == 3);
    assert(A.minimalTime(
                	-10, {2, 3, 4, 500, 6, 7, 8}) == 11);
    assert(A.minimalTime(
                1000000000, {1, 2}) == 666666667);
    assert(A.minimalTime(
                	196473025, {64112, 182044, 68726, 385968, 867871, 844789, 1187017, 278317, 980803, 549298, 727676, 387136, 314835, 642748, 44343, 340739, 452111, 282846, 723240, 605655, 357468, 226219, 1145957, 961676, 90329, 1205229, 1203245, 971773, 263837, 274288, 91855, 327948, 456331, 160580, 713915, 315819, 1005368, 666396, 594167, 751635, 207311, 313460, 1138770, 522145, 956207, 174730, 862883, 173782, 457607, 351555}) == 368);

    return 0;
}
