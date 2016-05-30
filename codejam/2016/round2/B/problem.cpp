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
#include <iomanip>
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

double solve_small(int n, int k, vector<double> p) {
  sort(all(p));
  double ans = 0.0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (__builtin_popcount(mask) == k) {
      double cand = 0;
      for (int sub = mask; sub; sub = (sub - 1) & mask) {
        assert((sub | mask) == mask);
        if (__builtin_popcount(sub) == k / 2) {
          double pr = 1.0;
          for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
              if (sub & (1 << i)) {
                pr *= p[i];
              } else {
                pr *= 1.0 - p[i];
              }
            }
          }
          cand += pr;
        }
      }
      ans = max(cand, ans);
    }
  }
  // debug(p);
  // cout << "mask: ";
  // for (int i = 0; i < n; ++i) {
  //  cout << ((best_mask >> i) & 1);
  //}
  // cout << "    ";
  return ans;
}

double solve2(const vector<double> &p) {
  int k = (int)p.size();
  vector<vector<double>> dp(k + 1, vector<double>(k + 1, 0.0));
  dp[k][k / 2] = 1.0;
  for (int pos = k - 1; pos >= 0; --pos) {
    for (int yes = 0; yes <= k / 2; ++yes) {
      dp[pos][yes] +=
          dp[pos + 1][yes + 1] * p[pos] + dp[pos + 1][yes] * (1.0 - p[pos]);
    }
  }
  return dp[0][0];
}

double solve_large(int k, vector<double> p) {
  sort(all(p));
  double ans = 0.0;
  int n = (int)p.size();
  for (int x = 0; x <= k; ++x) {
    int y = k - x;
    vector<double> g;
    for (int i = 0; i < x; ++i) {
      g.push_back(p[i]);
    }
    for (int i = n - y; i < n; ++i) {
      g.push_back(p[i]);
    }
    assert(g.size() == k);
    ans = max(ans, solve2(g));
  }
  return ans;
}

void solve_test() {
  int n, k;
  cin >> n >> k;
  vector<double> p(n);
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  double ans = solve_large(k, p);

  //  assert(fabs(ans - solve_small(n, k, p)) < EPS);
  std::cout << std::fixed;
  std::cout << std::setprecision(18) << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; ++t) {
    cout << "Case #" << t + 1 << ": ";
    solve_test();
  }
  return 0;
}
