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

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vi p(n);
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
    --p[i];
  }
  vii go(20, vi(n, 0));
  go[0] = p;
  auto p2 = p;
  for (int i = 1; i < 20; ++i) {
    for (int j = 0; j < n; ++j) {
      go[i][j] = go[i - 1][go[i - 1][j]];
    }
  }
  vector<int> ans(n, -1);
  vector<bool> done(n);
  vector<int> roots;
  int own_root = -1;
  ;
  for (int i = 0; i < n; ++i) {
    int lim = go.back()[i];
    if (done[lim]) {
      continue;
    }
    if (p[lim] != lim) {
      int cur = p[lim];
      done[lim] = 1;
      while (cur != lim) {
        done[cur] = 1;
        cur = p[cur];
      }
      p2[lim] = -1;
      roots.push_back(lim);
    } else {
      if (own_root == -1) {
        own_root = lim;
      }
      roots.push_back(lim);
    }
  }
  if (own_root == -1) {
    own_root = roots[0];
  }
  for (int i = 0; i < (int)roots.size(); ++i) {
    p2[roots[i]] = own_root;
  }
  int d = 0;
  for (int i = 0; i < n; ++i) {
    d += p2[i] != p[i];
  }
  cout << d << "\n";
  for (int x : p2) {
    cout << x + 1 << " ";
  }
  cout << "\n";
  return 0;
}
