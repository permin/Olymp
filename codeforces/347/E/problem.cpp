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

int dp[21][1 << 20];
int distances[1 << 20];

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<string> field(n);
  for (int i = 0; i < n; ++i) {
    cin >> field[i];
  }
  for (int i = 0; i < m; ++i) {
    int mask = 0;
    for (int j = 0; j < n; ++j) {
      // inv
      if (field[j][i] == '0') {
        mask ^= 1 << j;
      }
    }
    dp[0][mask] += 1;
    // debug(mask);
  }

  for (size_t bit = 1; bit < (1 << n); bit *= 2) {
    for (int d = n - 1; d >= 0; --d) {
      for (int mask = 0; mask < (1 << n); ++mask) {
        dp[d + 1][mask ^ bit] += dp[d][mask];
      }
    }
  }

  vi u(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (field[i][j] == '1') {
        u[i] += 1;
      }
    }
  }
  debug(u);
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int i = 0; i < n; ++i) {
      distances[mask] += (mask & (1 << i)) ? m - u[i] : u[i];
    }
  }

  int res = INF;
  for (int mask = 0; mask < (1 << n); ++mask) {
    int steps = 0;
    for (int d = 0; d <= n; ++d) {
      /*if (mask == 75) {
        debug(d);
        debug(dp[d][mask]);
      }*/
      if (d < n - d) {
        steps += dp[d][mask] * (n - d - d);
      }
    }
    if (steps > 0) {
      // debug(mask);
      // debug(steps);
    }
    res = min(res, distances[mask] - steps);
  }
  cout << res << "\n";

  return 0;
}
