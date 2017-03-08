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

bool in(ll x, ll y, ll sqx, ll sqy, ll side) {
  return sqx <= x && x <= sqx + side && sqy <= y && y <= sqy + side;
}

vector<ll> u(vector<ll> v) {
  sort(all(v));
  v.erase(unique(all(v)), v.end());
  return v;
}

void solve_test() {
  int n;
  cin >> n;
  ll side;
  cin >> side;
  vector<ll> px(n);
  vector<ll> py(n);
  for (int i = 0; i < n; ++i) {
    cin >> px[i] >> py[i];
  }

  vector<ll> uniq_x = u(px);
  vector<ll> uniq_y = u(py);
  int res = 0;
  for (ll sqx1 : uniq_x) {
    for (ll sqy1 : uniq_y) {
      for (ll sqx2 : uniq_x) {
        for (ll sqy2 : uniq_y) {
          int k = 0;
          for (int i = 0; i < n; ++i) {
            if (in(px[i], py[i], sqx1, sqy1, side) ||
                in(px[i], py[i], sqx2, sqy2, side)) {
              ++k;
            }
          }
          res = max(k, res);
        }
      }
    }
  }

  cout << res << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int test_index = 0; test_index < tests; ++test_index) {
    cout << "Case #" << test_index + 1 << ": ";
    solve_test();
  }
  return 0;
}
