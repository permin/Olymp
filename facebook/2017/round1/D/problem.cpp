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

const int kModulo = 1000 * 1000 * 1000 + 7;

int add(int x, int y) { return (x + y) % kModulo; }
int mul(int x, int y) { return int((1LL * x * y) % kModulo); }

int modPow(int x, int n) {
  int r = 1;
  while (n != 0) {
    if ((n & 1) != 0) {
      r = mul(r, x);
      --n;
    } else {
      x = mul(x, x);
      n /= 2;
    }
  }
  return r;
}

int inv(int x) { return modPow(x, kModulo - 2); }

int fact(int n) {
  int r = 1;
  for (int i = 1; i <= n; ++i) {
    r = mul(r, i);
  }
  return r;
}

int f(int line, int pieces) {
  int num = 1;
  int den = 1;
  for (int i = 0; i < pieces - 1; ++i) {
    num = mul(num, line + pieces - 1 - i);
    den = mul(den, pieces - 1 - i);
  }
  return mul(num, inv(den));
}

void solve_test() {
  int n, m;
  cin >> n >> m;
  vi r(n);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> r[i];
    sum += 2 * r[i];
  }
  int res = 0;
  map<int, int> ans;
  if (n == 1) {
    cout << m << "\n";
  } else {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j) {
          continue;
        }
        int space = m - 1 - sum + r[i] + r[j];
        if (space < 0) {
          continue;
        }
        if (ans.count(space) == 0) {
          ans[space] = mul(fact(n - 2), f(space, n + 1));
        }
        res = add(res, ans.at(space));
      }
    }
    cout << res << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int test_index = 0; test_index < tests; ++test_index) {
    cerr << "Case #" << test_index + 1 << ": \n";
    cout << "Case #" << test_index + 1 << ": ";
    solve_test();
  }
  return 0;
}
