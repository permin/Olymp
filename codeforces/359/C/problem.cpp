#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

#if GCC_VERSION > 40900
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#endif
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": " << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template <class T>
class IsIterable__ {
  static void f(...);
  template <class U>
  static typename U::const_iterator f(const U &);

 public:
  const static bool value =
      !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S>
ostream &operator<<(ostream &o, const pair<F, S> &p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C>
void O__(ostream &o, const C &c) {
  bool f = 1;
  for (const auto &x : c) {
    if (!f) {
      o << ", ";
    }
    if (IsIterable__<decltype(x)>::value) {
      o << "\n";
    }
    f = 0;
    o << x;
  }
}

template <class T>
ostream &operator<<(ostream &o, const vector<T> &v) {
  o << "[";
  O__(o, v);
  o << "]";
  return o;
}

template <class T, class V>
ostream &operator<<(ostream &o, const map<T, V> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

template <class T>
ostream &operator<<(ostream &o, const set<T> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

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
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

template <class F>
ll doit(const vector<ll> &x, const vector<ll> &y, const vector<ll> &z, F f) {
  ll m = LLINF;
  ll M = -LLINF;
  for (int i = 0; i < (int)x.size(); ++i) {
    m = min(m, f(x[i], y[i], z[i]));
    M = max(M, f(x[i], y[i], z[i]));
  }
  return (M + m) / 2;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t-- > 0) {
    int n;
    cin >> n;
    vector<ll> x(n);
    vector<ll> y(n);
    vector<ll> z(n);
    for (int i = 0; i < n; ++i) {
      cin >> x[i] >> y[i] >> z[i];
      x[i] *= 4;
      y[i] *= 4;
      z[i] *= 4;
    }
    ll a = doit(x, y, z, [](ll X, ll Y, ll Z) { return X + Y + Z; });
    ll b = doit(x, y, z, [](ll X, ll Y, ll Z) { return X + Y - Z; });
    ll c = doit(x, y, z, [](ll X, ll Y, ll Z) { return X - Y + Z; });
    ll d = doit(x, y, z, [](ll X, ll Y, ll Z) { return X - Y - Z; });
    ll ans_x = (a + d) / 2;
    ll ans_y = (a + b - 2 * ans_x) / 2;
    ll ans_z = a - ans_x - ans_y;
    assert(ans_x + ans_y + ans_z == a);
    assert(ans_x + ans_y - ans_z == b);
    assert(ans_x - ans_y - ans_z == d);
    assert(ans_x - ans_y + ans_z == c);
    cout << ans_x / 4 << " " << ans_y / 4 << " " << ans_z / 4 << "\n";
  }
  return 0;
}
