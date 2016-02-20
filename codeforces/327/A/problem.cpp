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

int get(const vi& a, int i) {
    int n = (int)a.size();
    int v = -1;
    if (i < 0) {
        v = a[0];
    } else if (i >= n) {
        v = a.back();
    } else {
        v = a[i];
    }
    return v;
}

vi process(const vi& a, int w) {
    vi res(a.size(), -1);
    int u = 0;
    int z = 0;
    int n = (int)a.size();
    int M = 4 * n;
    for (int i = -M; i <= n + M; ++i) {
        int v = get(a, i);
        if (v)
            ++u;
        else
            ++z;
        if (i - w >= -M) {
            int v2 = get(a, i - w);
            if (v2)
                --u;
            else
                --z;
            assert(v >= 0 && v <= 1 && v2 >= 0 && v2 <= 1);
        }
        int j = i - (w/2);
        if (j >= 0 && j < n) {
            res[j] = (u > z);
            assert(u + z == w);
        }
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    int lower = -1;
    int upper = n;
    while (lower + 1 < upper) {
        int med = (1 + lower + upper)/ 2;
        vi ta = process(a, 2 * med + 1);
        debug(med);
        debug(process(ta, 3) == ta);
        if (process(ta, 3) == ta) {
            upper = med;
        } else {
            lower = med;
        }
    }
    debug(upper);
    vi ta = process(a, 2 * upper+ 1);
    {
        vi b(a);
        int k = 0;
        while(b != process(b, 3)) {
            b = process(b,3);
            debug(b);
            ++k;
        }
        debug(k);
    }
    if (process(ta, 3) == ta) {
        cout << upper<< "\n";
        return 0;
        for (int i: ta) {
            cout << i << " ";
        }
    } else {
        cout << "-1";
    }
    return 0;
}
