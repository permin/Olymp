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
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

void dfs(int v, const vii &al, vector<bool> &used) {
  if (used[v])
    return;
  used[v] = 1;
  for (int v2 : al[v]) {
    dfs(v2, al, used);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<ll> x(n);
  vector<ll> y(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i];
  }

  long long lower = 0;
  long long upper = 2 * 1000 * 1000 * 1000 + 10;
  while (lower + 1 < upper) {
    long long med = (lower + upper) / 2;
    vii al(n);
    for (int d = -1; d <= +1; d += 2) {
      vector<pair<long long, int>> f;
      for (int i = 0; i < n; ++i) {
        f.emplace_back(x[i] + d * y[i], i);
      }
      sort(all(f));
      for (int i = 0; i < n; ++i) {
        if (f[0].first + med <= f[i].first) {
          al[f[0].second].push_back(f[i].second);
          al[f[i].second].push_back(f[0].second);
        }
        if (f[i].first + med <= f[n - 1].first) {
          al[f[n - 1].second].push_back(f[i].second);
          al[f[i].second].push_back(f[n - 1].second);
        }
      }
    }
    vector<bool> used(n);
    dfs(0, al, used);
    bool ok = 1;
    for (int i = 0; i < n; ++i) {
      if (!used[i])
        ok = 0;
    }
    if (ok) {
      lower = med;
    } else {
      upper = med;
    }
  }
  cout << lower << "\n";

  return 0;
}
