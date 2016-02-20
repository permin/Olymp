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
    if (!f)
      o << ", ";
    if (IsIterable__<decltype(x)>::value)
      o << "\n";
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

const int MOD = int(1e9 + 7);

int add(int x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
  return x;
}

int mul(int x, int y) { return int((1LL * x * y) % MOD); }

int dp[1 << 21][21];
int n, k, L;
size_t super_mask;

int solve(size_t subsums, int pos) {
  if (subsums & (1 << k)) {
    subsums = (1 << k);
  }
  if (pos == n) {
    if (subsums & (1 << k)) {
      return 1;
    } else {
      return 0;
    }
  }
  int &res = dp[subsums][pos];
  if (res >= 0) {
    return res;
  }
  res = 0;
  if ((1 << k) == subsums) {
    return res = mul(L + 1, solve(subsums, pos + 1));
  }
  for (int i = 0; i <= k && i <= L; ++i) {
    res = add(res, solve(super_mask & (subsums | (subsums << i)), pos + 1));
  }
  if (k + 1 <= L) {
    res = add(res, mul(L - k, solve(subsums, pos + 1)));
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    cin >> n >> k >> L;
    memset(dp, -1, sizeof(dp));
    super_mask = (1 << (k + 1)) - 1;
    cout << solve(1, 0) << "\n";
  }
  return 0;
}
