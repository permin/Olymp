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
const int INF = std::numeric_limits<int>::max() / 4;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

void dfs(int v, const vii &al, vii &dp, int p = -1) {
  debug(v);
  /*if (al[v].size() == 1 && (p != -1)) {
    dp[v][0] = dp[v][1] = 0;
    return;
  }*/
  vector<pii> delta;
  int missing_all = 0;
  for (int v2 : al[v]) {
    if (v2 != p) {
      dfs(v2, al, dp, v);
      delta.emplace_back(dp[v2][1] - dp[v2][0], v2);
      missing_all += dp[v2][0];
    }
  }
  debug(missing_all);
  debug(delta);
  int d = static_cast<int>(al[v].size()) - static_cast<int>(p != -1);
  assert(d == static_cast<int>(delta.size()));
  sort(all(delta));
  dp[v][0] = dp[v][1] = INF;
  for (int out = 0; out <= 2 && out <= d; ++out) {
    for (int in = 0; in < 2; ++in) {
      if (in + out <= 2) {
        int deltas = 0;
        if (out >= 1) {
          deltas += delta[0].first;
        }
        if (out >= 2) {
          deltas += delta[1].first;
        }
        dp[v][in] = min(dp[v][in], missing_all + d - out + deltas);
      }
    }
  }
  assert(dp[v][0] >= 0);
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  ll new_cost, old_cost;
  cin >> n >> new_cost >> old_cost;
  if (n == 2) {
    cout << new_cost << "\n";
    return 0;
  }
  if (n == 3) {
    cout << min(new_cost + new_cost, new_cost + old_cost) << "\n";
    return 0;
  }
  vi deg(n);
  vii al(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    al[a].push_back(b);
    al[b].push_back(a);
    deg[a] += 1;
    deg[b] += 1;
  }

  int root =
      static_cast<int>(std::distance(deg.begin(), min_element(all(deg))));
  assert(deg[root] == 1);

  if (new_cost == old_cost) {
    cout << new_cost * (n - 1) << "\n";
    return 0;
  }
  if (new_cost > old_cost) {
    ll res = old_cost * (n - 1);
    if (*max_element(all(deg)) == n - 1) {
      res -= old_cost;
      res += new_cost;
    }
    cout << res << "\n";
    return 0;
  }

  vii dp(n, vi(2, -INF));
  dfs(root, al, dp);
  debug(root);

  int missing_edges = dp[root][0];
  debug(dp);
  debug(missing_edges);
  cout << old_cost * (missing_edges) + (n - 1 - missing_edges) * new_cost
       << "\n";

  return 0;
}
