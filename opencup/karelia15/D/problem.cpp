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

int gcd(int x, int y) {
    while(x) {
        y %= x;
        swap(x, y);
    }
    return y;
}

int sign(int x) {
    if (x == 0)
        return 0;
    if (x > 0)
        return +1;
    return -1;
}

pii norm(pii A) {
    int d = gcd(abs(A.first), abs(A.second));
    if (d > 0) {
        A.first /= d;
        A.second /= d;
    }
    if (A.second < 0) {
        A.first *= -1;
        A.second *= -1;
    }
    if (A.second == 0 || A.first == 0) {
        A.first = abs(sign(A.first));
        A.second = abs(sign(A.second));
    }
    return A;
}

bool dfs(int i, const vii& am, vector<bool>& used, vi& R) {
    if (used[i])
        return 0;
    used[i] = 1;
    for (int j = 0; j < am[i].size(); ++j) {
        if (am[i][j]) {
            if (R[j] == -1 || dfs(R[j], am, used, R)) {
                R[j] = i;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    /*debug(norm({1,1}));
    debug(norm({-1,-1}));
    debug(norm({1,-1}));
    debug(norm({-1,1}));
    debug(norm({18,18}));
    debug(norm({-18,-18}));
    debug(norm({18,-18}));
    debug(norm({-18,18}));
    debug(norm({0,18}));
    debug(norm({0,-18}));
    debug(norm({0,-18}));
    debug(norm({0,18}));
    debug(norm({18,88}));
    debug(norm({-18,-88}));
    debug(norm({18,-88}));
    debug(norm({-18,88}));
    debug(norm({18,0}));
    debug(norm({-18,0}));
    debug(norm({18,0}));
    debug(norm({-18,0}));*/

    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    while(tests --> 0) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i] >> c[i];
        }
        map<pii, int> x;
        map<pii, int> y;

        int x_eq_0 = -1;
        int vert_x_neq_0 = -1;

        vii am(n, vi(n, 0));

        for (int i = 0; i < n; ++i) {
            if (b[i] == 0) {
                if (c[i] == 0)
                    x_eq_0 = i;
                else
                    vert_x_neq_0 = i;
            } else {
                pii xx = norm(pii(a[i], b[i]));
                pii yy = norm(pii(c[i], b[i]));
                int xi = x.count(xx) ? x[xx] : int(x.size());
                int yi = y.count(yy) ? y[yy] : int(y.size());
                x[xx] = xi;
                y[yy] = yi;
                am[xi][yi] = i + 1;
            }
        }
        am.resize(x.size());
        for (int i = 0; i < am.size(); ++i)
            am[i].resize(y.size());

        vector<int> R(am[0].size(), -1);
        //debug(am);
        vector<bool> assigned(am.size(), false);
        {
            for (int i = 0; 1 && i < am.size(); ++i) {
                for (int j = 0; j < am[i].size(); ++j) {
                    if (am[i][j]) {
                        if (R[j] == -1) {
                            R[j] = i;
                            assigned[i] = 1;
                            break;
                        }
                    }
                }
            }

            //assigned.assign(am.size(), 0);

            for (int i = 0; i < am.size(); ++i) {
                if (assigned[i])
                    continue;
                vector<bool> used(am.size(), false);
                dfs(i, am, used, R);
            }
        }
        vector<int> ans;
        for (int i = 0; i < am[0].size(); ++i) {
            if (R[i] >= 0)
                ans.push_back(am[R[i]][i]);
        }
        if (vert_x_neq_0 != -1)
            ans.push_back(vert_x_neq_0 + 1);
        if (ans.empty() && x_eq_0 != -1)
            ans.push_back(x_eq_0 + 1);
        cout << ans.size() << " ";
        for (int x2: ans)
            cout << x2 << " ";
        cout << "\n";
    }
    return 0;
}
