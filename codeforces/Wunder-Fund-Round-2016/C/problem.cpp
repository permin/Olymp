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

template <class T> class IsIterable__ {
  static void f(...);
  template <class U> static typename U::const_iterator f(const U &);

public:
  const static bool value =
      !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S>
ostream &operator<<(ostream &o, const pair<F, S> &p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C> void O__(ostream &o, const C &c) {
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

template <class T> ostream &operator<<(ostream &o, const vector<T> &v) {
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

template <class T> ostream &operator<<(ostream &o, const set<T> &v) {
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

ll distL1(ll x, ll y, ll a, ll b) { return labs(x - a) + labs(y - b); }

ll det2(ll a, ll b, ll c, ll d) { return 1LL * a * d - 1LL * b * c; }

ll area(ll x0, ll y0, ll x1, ll y1, ll x2, ll y2) {
  return 1LL * x0 * det2(y1, 1, y2, 1) - 1LL * y0 * det2(x1, 1, x2, 1) +
         1LL * det2(x1, y1, x2, y2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<ll> x(n);
  vector<ll> y(n);
  for (ll i = 0; i < n; ++i) {
    cin >> x[i] >> y[i];
  }
  int a = 0;
  int b = 0;
  if (a == b) {
    ++b;
  }
  for (int i = 1; i < n; ++i) {
    if (distL1(x[a], y[a], x[i], y[i]) < distL1(x[a], y[a], x[b], y[b])) {
      b = i;
    }
  }
  int c = -1;
  for (int i = 1; i < n; ++i) {
    if (area(x[a], y[a], x[b], y[b], x[i], y[i]) != 0) {
      if (c == -1 ||
          (distL1(x[a], y[a], x[i], y[i]) + distL1(x[b], y[b], x[i], y[i])) <
              (distL1(x[a], y[a], x[c], y[c]) +
               distL1(x[b], y[b], x[c], y[c]))) {
        c = i;
      }
    }
  }
  assert(c != -1);
  assert(a != b && a != c && b != c);
  assert(area(x[a], y[a], x[b], y[b], x[c], y[c]) != 0);
  vector<int> res;
  res.push_back(a + 1);
  res.push_back(b + 1);
  res.push_back(c + 1);
  sort(all(res));
  cout << res[0] << " ";
  cout << res[1] << " ";
  cout << res[2] << "\n";
  return 0;
}
