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

class ArmyTeleportation {
public:
    bool solve(int x0, int y0, int x1, int y1, int x, int y) {
        debug("solve");
        int M = 2e6;
        for (int a = -M; a <= M; a += 2) {
            ll X = 1LL * x - 1LL * a * x0;
            ll Y = 1LL * y - 1LL * a * y0;
            bool ok = 0;
            if (x1 == 0 && y1 == 0) {
                ok = ok || (X == 0 && Y == 0);
            }
            if (x1 == 0) {
                ok = ok || (X == 0 && Y % (2 * y1) == 0);
            }
            if (y1 == 0) {
                ok = ok || (Y == 0 && X % (2 * x1) == 0);
            }
            ok = ok || (X % (2 * x1) == 0 && Y % (2 * y1) == 0);
            if (ok)
                return 1;
        }
        return 0;
    }

    string ifPossible(
            vector <int> x1, vector <int> y1,
            vector <int> x2, vector <int> y2
            , vector <int> xt, vector <int> yt)  {
        for (int i =0 ; i < x2.size(); ++i) {
            for (int sign = -1; sign <= +1; sign += 2) {
                int dx = x2[i] - sign * x1[0];
                int dy = y2[i] - sign * y1[0];
                vector<bool> used(x1.size());
                used[i] = 1;
                bool ok = 1;
                for (int j = 1; j < x1.size(); ++j) {
                    bool cur = 0;
                    for (int k = 0; k < x2.size(); ++k) {
                        if (used[k])
                            continue;
                        if (x2[k] == dx + sign * x1[j] &&
                            y2[k] == dy + sign * y1[j]) {
                            used[k] = 1;
                            cur = 1;
                            break;
                        }
                    }
                    ok = ok && cur;
                }
                if (!ok) {
                    continue;
                }
                int koe = sign == +1 ? 0 : 2;

                if (solve(xt[0] - xt[2], yt[0] - yt[2],
                          xt[1] - xt[2], yt[1] - yt[2],
                          dx + koe * xt[2],
                          dy + koe * yt[2])) {
                    return f(1);
                }
            }
        }
        return f(0);
    }
    string f(bool x) {
        return x? "possible" : "impossible";
    }
};



int main() {
    ArmyTeleportation A;
    debug(A.ifPossible(
{6, -5, 1},
{3, -10, -7},
{0, 11, 5},
{-5, 8, 5},
{0, -5, 4},
{-8, -9, -4}));
    /*set<vector<int>> q;
    q.insert({0,0,0, 1});
    int n = 20;
    for (int i = 0; i < n; ++i) {
        vii add;
        for (const auto& x: q) {
            vi y = x;
            add.push_back({2 - y[0],-y[1], -y[2], -y[3]});
            add.push_back({-y[0],2-y[1], -y[2], -y[3]});
            add.push_back({-y[0],-y[1], 2-y[2], -y[3]});
        }
        for (const auto& x: add) {
            q.insert(x);
        }
    }
    for (auto x: q) {
        assert(x.back() == ((abs(x[0] + x[1] + x[2])/2)&1)?-1:1);
        int sum = x[0] + x[1] + x[2];
        assert(sum ==0 || sum == 2);
    }
    debug(q);*/
    return 0;
}
