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

const int M = 100000;

int f[M];
int solve(int x) {
  if (f[x] >= 0)
    return f[x];
  int &res = f[x];
  if (x == 0) {
    return res = 0;
  }
  if (x % 2 == 1) {
    int a = solve(x - 1);
    if (a == 0)
      return res = 1;
    else
      return res = 0;
  } else {
    int a = solve(x / 2);
    int b = solve(x - 1);
    res = 0;
    while (a == res || b == res)
      ++res;
  }
  return res;
}

int appr(int x) {
  if (x % 2) {
    return x == 3;
  }
  int a = appr(x / 2);
  if (a == 1)
    return 2;
  return 1;
}

void out(int r) { cout << (r == 0 ? "Nicky" : "Kevin") << "\n"; }

int main() {
  std::ios_base::sync_with_stdio(false);
  for (int i = 0; i < M; ++i)
    f[i] = -1;
  for (int i = 0; i < 20; ++i) {
    cerr << i << " " << solve(i) << "\n";
  }
  for (int i = 1; i < M; ++i) {
    // cerr << i << " " << solve(i) << " " << appr(i) << "\n";
    assert(solve(i) < 3);
    if (i >= 10 && appr(i) != solve(i)) {
      debug(i);
    }
  }
  int n;
  cin >> n;
  int k = 0;
  cin >> k;
  if (k % 2) {
    int r = 0;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      if (x < 10) {
        r ^= solve(x);
      } else {
        r ^= appr(x);
      }
    }
    out(r);
  } else {
    int r = 0;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      if (x == 1) {
        r ^= 1;
      } else if (x == 2) {
        r ^= 2;
      } else if (x % 2 == 0) {
        r ^= 1;
      }
    }
    out(r);
  }
  return 0;
}
