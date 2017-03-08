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

vii solve(string a, string b) {
  int n = (int)a.size();
  int m = (int)b.size();
  vii dp(n + 1, vi(m + 1, 0));
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else {
        int res = max(dp[i][j - 1], dp[i - 1][j]);
        if (a[i - 1] == b[j - 1]) {
          res = max(res, dp[i - 1][j - 1] + 1);
        } else {
          res = max(res, dp[i - 1][j - 1]);
        }
        dp[i][j] = res;
      }
    }
  }
  return dp;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  string a, b;
  cin >> a >> b;
  vii pref = solve(a, b);
  reverse(all(a));
  reverse(all(b));
  vii suff = solve(a, b);
  reverse(all(a));
  reverse(all(b));
  vii ok(a.size() + 1, vi(256, 0));
  int ans = pref[a.size()][b.size()];
  for (int i = 0; i <= (int)a.size(); ++i) {
    for (int match = 0; match < (int)b.size(); ++match) {
      if (ans + 1 ==
          1 + pref[i][match] +
              suff[(int)a.size() - i][(int)b.size() - match - 1]) {
        ok[i][b[match]] = 1;
      }
    }
  }
  debug(ans);
  int res = 0;
  for (const auto &line : ok) {
    for (int x : line) {
      res += x;
    }
  }
  cout << res << "\n";

  return 0;
}
