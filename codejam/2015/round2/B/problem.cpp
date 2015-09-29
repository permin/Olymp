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
typedef pair<long double, long double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const long double PI = 3.1415926535897932384626433832795;
const long double EPS = 1e-13;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

bool eq(long double x, long double y) {
    return fabs(x-y) < EPS;
}

long double solve1(long double r1, long double c1, long double V, long double X) {
    if (!eq(c1, X)) {
        return -1.0;
    }
    return V / r1;
}

long double det2(long double a, long double b, long double c, long double d) {
    return a * d - b * c;
}

pdd solveKramer(long double a11, long double a12, long double b1,
        long double a21, long double a22, long double b2) {
    long double d =  det2(a11, a12, a21, a22);
    if (eq(d, 0))
        return pdd(-1,-1);
    long double x1, x2;
    x1 = det2(b1, a12, b2, a22) / d;
    x2 = det2(a11, b1, a21, b2) / d;
    assert(eq(a11 * x1 + a12 * x2, b1));
    assert(eq(a21 * x1 + a22 * x2, b2));
    return pdd(x1,x2);
}

long double solve2(long double r1, long double c1, long double r2, long double c2, long double V, long double X) {
    if (eq(c1, X) && eq(c2, X)) {
        return V / (r1 + r2);
    }
    pdd ans = solveKramer(
            r1, r2, V,
            r1 * (c1 - X), r2 * (c2 - X), 0.0);
    if (ans.first < 0 || ans.second < 0) {
        return -1;
    }
    long double t1 = ans.first;
    long double t2 = ans.second;
    assert(eq(t1 * r1 + t2 * r2, V));
    long double v1 = t1 * r1;
    long double v2 = t2 * r2;
    assert(eq(v1+v2, V));
    assert(eq((c1 * v1 + c2 * v2) / (v1 + v2), X));
    return max(ans.first, ans.second);
}

void solve() {
    int n;
    cin >> n;
    /*if (n == 1) {
        long double V, X;
        long double r1, c1;
        cin >> V >> X;
        cin >> r1 >> c1;

        long double a = solve1(r1, c1, V, X);
        if (a < 0) {
            cout << "IMPOSSIBLE\n";
        } else {
            printf("%0.18lf\n", double(a));
        }
        return;
    } else if (n == 2) {
        long double V, X;
        long double r1, c1;
        cin >> V >> X;
        cin >> r1 >> c1;
        long double r2, c2;
        cin >> r2 >> c2;
        long double a = solve2(r1, c1, r2, c2, V, X);

        if (a < 0) {
            cout << "IMPOSSIBLE\n";
        } else {
            printf("%0.18lf\n", double(a));
        }
        return;
    } else {*/
        long double V, X;
        cin >> V >> X;
        vector<pdd> rc(n);
        for (int i = 0; i < n; ++i) {
            cin >> rc[i].first >> rc[i].second;
        }
        bool solved = false;
        vector<pdd> hot;
        vector<pdd> ok;
        vector<pdd> cold;
        for (int i =0 ; i < n; ++i) {
            if (rc[i].second < X) {
                cold.push_back(rc[i]);
            }
            if (rc[i].second > X) {
                hot.push_back(rc[i]);
            }
            if (eq(rc[i].second, X)) {
                ok.push_back(rc[i]);
            }
        }
            long double lower = 0;
            long double upper = 1e40;
            for (int it = 0; it < 600; ++it) {
                long double t = (lower + upper) / 2.0;
                long double Vcopy = V;
                for (size_t i = 0; i < ok.size(); ++i) {
                    Vcopy -= ok[i].first * t;
                }
                long double costHot = 0;
                long double costCold = 0;
                long double weightHot = 0;
                long double weightCold = 0;
                for (size_t i = 0; i < hot.size(); ++i) {
                    costHot += fabs(hot[i].second - X) * hot[i].first * t;
                    weightHot += hot[i].first * t;
                }
                for (size_t i = 0; i < cold.size(); ++i) {
                    costCold += fabs(cold[i].second - X) * cold[i].first * t;
                    weightCold += cold[i].first * t;
                }
                if (eq(costHot, costCold)) {
                    Vcopy -= weightHot;
                    Vcopy -= weightCold;
                } else {
                    if (costHot < costCold) {
                        //long double r = costHot / costCold;
                        Vcopy -= weightHot;
                        //Vcopy -= r * weightCold;
                    }
                    if (costHot > costCold) {
                        //long double r = costCold / costHot;
                        //Vcopy -= r * weightHot;
                        Vcopy -= weightCold;
                    }
                }
                if (Vcopy <= 0.0) {
                    solved = 1;
                    upper = t;
                } else {
                    lower = t;
                }
            }
            if (solved)
                printf("%0.18f\n", double(lower));
            else
                printf("IMPOSSIBLE\n");

        return;
    //}
    cout << "\n";
}

int main() {
    //std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<<t+1<<": ";
        solve();
    }
    return 0;
}
