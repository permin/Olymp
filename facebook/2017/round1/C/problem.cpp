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
const int INF = std::numeric_limits<int>::max() / 2 - 1000;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

int solve(int city, int delivered, int on_board, const vi &start, const vi &end,
          const vii &am, viii &dp) {
  int &res = dp[city][delivered][on_board];
  if (res >= 0) {
    return res;
  }
  res = INF;
  int families = (int)start.size();
  if (delivered == families) {
    return res = 0;
  }
  const int d = delivered;
  if (on_board == 0) {
    res = min(res,
              solve(start[d], d, 1, start, end, am, dp) + am[city][start[d]]);
  } else if (on_board == 1) {
    res = min(res,
              solve(end[d], d + 1, 0, start, end, am, dp) + am[city][end[d]]);
    if (d + 1 < (int)start.size()) {
      res = min(res, solve(start[d + 1], d, 2, start, end, am, dp) +
                         am[city][start[d + 1]]);
    }
  } else {
    res = min(res,
              solve(end[d], d + 1, 1, start, end, am, dp) + am[city][end[d]]);
  }
  return res;
}

void solve_test() {
  int n, m, families;
  cin >> n >> m >> families;
  vii am(n, vi(n, INF));
  for (int i = 0; i < n; ++i) {
    am[i][i] = 0;
  }
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    am[a][b] = min(am[a][b], c);
    am[b][a] = min(am[b][a], c);
  }
  vi start(families);
  vi end(families);
  for (int i = 0; i < families; ++i) {
    cin >> start[i] >> end[i];
    --start[i];
    --end[i];
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        am[i][j] = min(am[i][j], am[i][k] + am[k][j]);
      }
    }
  }

  viii dp(n, vii(families + 1, vi(3, -1)));
  int res = solve(0, 0, 0, start, end, am, dp);
  if (res >= INF) {
    res = -1;
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
