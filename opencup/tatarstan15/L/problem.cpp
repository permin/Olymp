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

void upd(int val, int add, int& num, int VAL) {
    if (val == VAL)
        num += add;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int M = *(max_element(all(a)));
    int C = (int)count(all(a), M);
    int C_prev = (int)count(all(a), M - 1);

    ll best = 1LL * M * C;

    for (int i = 0; i < n; ++i) {
        for (int dx: {-1, +1}) {
            int ni = i + dx;
            if (ni >= 0 && ni < n && a[i] > 0) {
                int x = a[i];
                int y = a[ni];

                int nx = a[i] - 1;
                int ny = a[ni] + 1;

                int C_copy = C;
                int C_prev_copy = C_prev;
                int C_next_copy = 0;

                for (int z: {x,y}) {
                    upd(z, -1, C_copy, M);
                    upd(z, -1, C_prev_copy, M - 1);
                }
                for (int z: {nx,ny}) {
                    upd(z, +1, C_next_copy, M + 1);
                    upd(z, +1, C_copy, M);
                    upd(z, +1, C_prev_copy, M - 1);
                }
                ll cur = 0;
                if (C_next_copy > 0) {
                    cur = 1LL * (M + 1) * C_next_copy;
                } else if (C_copy > 0) {
                    cur = 1LL * (M) * C_copy;
                } else if (C_prev_copy > 0) {
                    cur = 1LL * (M - 1) * C_prev_copy;
                } else {
                    assert(false);
                }
                best = min(best, cur);
            }
        }
    }
    cout << best << "\n";
    return 0;
}
