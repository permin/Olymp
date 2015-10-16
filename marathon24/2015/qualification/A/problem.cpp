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

vi order(int n) {
    int p = 0;
    vi res;
    int step = n-1;
    int dir = +1;
    for (int i = 0 ;i < n; ++i) {
        res.push_back(p);
        p += dir * step;
        --step;
        dir = -dir;
    }
    return res;
}

void t(vii& a) {
    vii b(a[0].size(), vi(a.size(), -1));
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)a[0].size(); ++j)
            b[j][i] = a[i][j];
    }
    a = b;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    bool f = 0;
    if (m > n) {
        swap(n,m);
        f = 1;
    }
    vii ans(n, vi(m, -1));
    vi cols = order(m);
    vi rows = order(n);
    int y = 0;
    int id = 0;
    for (int c: cols) {
        vi rows2 = rows;
        if (y != 0) {
            reverse(all(rows2));
        }
        for (int i: rows2) {
            ans[i][c] = id;
            ++id;
        }
        y = rows2.back();
    }
    if (f)
        t(ans);
    for (auto line: ans) {
        for (int x: line) {
            cout << x + 1 << " ";
        }
        cout << "\n";
    }
    return 0;
}
