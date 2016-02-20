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

const int mod = (int)1e9 + 7;

int mul(int x, int y) { return (int)(1LL * x * y % mod); }
int mod_pow(int x, int n) {
  int r = 1;
  while (n) {
    if (n & 1) {
      --n;
      r = mul(r, x);
    } else {
      n /= 2;
      x = mul(x, x);
    }
  }
  return r;
}

const int maxN = 3e5 + 10;
int fact[maxN];
int inv_fact[maxN];
int sum_req[maxN];
int sum_total[maxN];
int req[maxN];

int A(int n, int k) {
  if (k > n)
    return 0;
  return mul(fact[n], inv_fact[n - k]);
}

vii childs;
int dfs(int v) {
  if (childs[v].empty()) {
    if (req[v] > 1) {
      return 0;
    }
    sum_req[v] = req[v];
    sum_total[v] = 1;

    return 1;
  } else {
    int ways = 1;
    for (int v2 : childs[v]) {
      ways = mul(ways, dfs(v2));
      sum_total[v] += sum_total[v2];
      sum_req[v] += sum_req[v2];
    }

    if (sum_total[v] < sum_req[v] + req[v]) {
      ways = 0;
    } else {
      ways = mul(ways, A(sum_total[v] - sum_req[v], req[v]));
    }
    sum_req[v] += req[v];
    return ways;
  }
}

int dp[maxN][20];

int go_up(int x, int n) {
  for (int i = 19; i >= 0; --i) {
    if (n >= (1 << i)) {
      n -= 1 << i;
      x = dp[x][i];
    }
  }
  return x;
}

int depth[maxN];
void dfs(int v, int d) {
  depth[v] = d;
  for (int v2 : childs[v]) {
    dfs(v2, d + 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  for (int i = 0; i < maxN; ++i) {
    fact[i] = i ? mul(i, fact[i - 1]) : 1;
    inv_fact[i] = mod_pow(fact[i], mod - 2);
  }
  int n;
  int m;
  cin >> n >> m;
  childs.resize(n);

  for (int i = 1; i < n; ++i) {
    int p;
    cin >> p;
    --p;
    childs[p].push_back(i);
    dp[i][0] = p;
  }
  {
    for (int d = 1; d < 20; ++d) {
      for (int i = 0; i < n; ++i) {
        dp[i][d] = dp[dp[i][d - 1]][d - 1];
      }
    }
  }
  dfs(0, 0);
  int leafs = 0;
  for (int i = 0; i < n; ++i) {
    if (childs[i].empty())
      ++leafs;
  }
  vi request(leafs, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    int x = request[a];
    int y = b;
    if (depth[x] > depth[y])
      swap(x, y);
    if (x == y) {
      request[a] = x;
    } else {
      debug(x);
      debug(y);
      int delta = depth[y] - depth[x];
      debug(delta);
      int z = go_up(y, delta);
      debug(z);
      assert(depth[z] == depth[x]);
      if (z == x) {
        request[a] = y;
      } else {
        assert(0);
        cout << 0 << "\n";
        exit(0);
      }
    }
  }
  for (int i : request)
    req[i] += 1;
  debug(request);

  cout << dfs(0) << "\n";
  return 0;
}
