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

const int maxN = 1000 * 1000;
int fact[maxN];
int inv_fact[maxN];
const int mod = 1000 * 1000 * 1000 + 7;
int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int mul(int x, int y) { return int((1LL * x * y) % mod); }

int mod_pow(int x, int n) {
  int r = 1;
  while (n) {
    if (n & 1) {
      r = mul(r, x);
      --n;
    } else {
      x = mul(x, x);
      n /= 2;
    }
  }
  return r;
}
int inv(int n) { return mod_pow(n, mod - 2); }

int C(int n, int k) {
  if (k > n) {
    return 0;
  }
  return mul(fact[n], mul(inv_fact[k], inv_fact[n - k]));
}

void solve() {
  int m, n;
  cin >> m >> n;
  int res = 0;
  int bound = m - n;
  vector<int> n_k(bound + 1);
  vector<int> n_m_k(bound + 1);
  for (int k = 0; k <= bound; ++k) {
    if (k == 0) {
      n_k[k] = 1;
      n_m_k[bound] = 1;
    } else {
      n_k[k] = mul(n_k[k - 1], n);
      n_m_k[bound - k] = mul(n_m_k[bound - k + 1], n - 1);
    }
  }
  for (int k = 0; k <= bound; ++k) {
    res = add(res, mul(C(m - k - 1, n - 1), mul(n_m_k[k], n_k[k])));
  }
  cout << res << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;

  for (int i = 0; i < maxN; ++i) {
    fact[i] = i == 0 ? 1 : mul(i, fact[i - 1]);
    inv_fact[i] = inv(fact[i]);
  }

  while (t-- > 0) {
    solve();
  }
  return 0;
}
