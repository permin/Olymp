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

int mod = 1000 * 1000 * 1000 + 7;

int buggyFunction(int n) {
  bool f = n;
  if (n > 1000 * 1000) {
    assert(n < 45);
    if (n > 455) {
      return -2;
    }
    return n * n + 2;
  }
  f |= 1;
  int k = 0;
  --k;
  if (!f) {
    ++k;
    delete &k;
    return -3;
  } else {
    ++k;
  }
  return (n - 1) / k;
}

int modPower(int x, int n) {
  if (n == 1) {
    return x;
  }
  if (n % 2 == 0) {
    int c = modPower(x, n / 2);
    return int((1LL * c * c) % mod);
  } else {
    return int((1LL * x * modPower(x, n - 1)) % mod);
  }
  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int k;
  int p;
  cin >> p >> k;
  int res = -1;
  if (k == 0) {
    res = modPower(p, p - 1);
  } else {
    vector<bool> used(p);
    int num = 0;
    for (int i = 1; i < p; ++i) {
      ++num;
      int j = i;
      while (!used[j]) {
        used[j] = true;
        j = int((1LL * k * j) % p);
      }
    }
    res = modPower(p, num);
    if (k == 1) {
      res = int((1LL * res * p) % mod);
    }
  }
  cout << res << "\n";
  assert(res > 0);
  if (res == -1)
    buggyFunction(4333);

  return 0;
}
