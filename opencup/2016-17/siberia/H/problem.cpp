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

class Fenwick {
 public:
  explicit Fenwick(int n) : data(n) {}
  void inc(size_t i, ll val) {
    for (; i < data.size(); i |= (i + 1)) {
      data[i] += val;
    }
  }
  ll sum(int r) {
    ll res = 0;
    while (r >= 0) {
      res += data[r];
      r = r & (r + 1);
      --r;
    }
    return res;
  }
  ll sum(int l, int r) {
    ll res = sum(r);
    if (l != 0) {
      res -= sum(l - 1);
    }
    return res;
  }
  vector<ll> data;
};

void dfs(int v, const vii &children, vi &tour) {
  tour.push_back(v);
  for (int v2 : children[v]) {
    dfs(v2, children, tour);
    tour.push_back(v);
  }
  if (children[v].empty()) {
    tour.push_back(v);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, q;
  cin >> n >> q;
  vii children(n + n + 1);
  vi current_weights(n + 1);
  for (int &x : current_weights) {
    cin >> x;
  }
  vi length_for_scales(n);
  for (int i = 0; i < n; ++i) {
    cin >> length_for_scales[i];
    int left, right;
    cin >> left >> right;
    if (left > 0) {
      children[i].push_back(left - 1);
    } else {
      children[i].push_back(n - left - 1);
    }
    if (right > 0) {
      children[i].push_back(right - 1);
    } else {
      children[i].push_back(n - right - 1);
    }
  }
  debug(children);
  vector<int> tour;
  dfs(0, children, tour);
  vi first(n + 1 + n, -1);
  vi last(n + 1 + n);
  for (int i = 0; i < static_cast<int>(tour.size()); ++i) {
    if (first[tour[i]] == -1) {
      first[tour[i]] = i;
    }
    last[tour[i]] = i;
  }
  Fenwick tree((int)tour.size());

  for (int i = 0; i < n + 1; ++i) {
    tree.inc(first[n + i], current_weights[i]);
  }
  vector<double> res;
  for (int i = 0; i < q; ++i) {
    int t;
    cin >> t;
    if (t == 1) {
      int id, w;
      cin >> id >> w;
      --id;
      tree.inc(first[id + n], -current_weights[id]);
      current_weights[id] = w;
      tree.inc(first[id + n], current_weights[id]);
    } else {
      int v;
      cin >> v;
      --v;
      int l = children[v][0];
      int r = children[v][1];
      ll left = tree.sum(first[l], last[l]);
      ll right = tree.sum(first[r], last[r]);
      debug(left);
      debug(right);
      res.push_back(1.0 * length_for_scales[v] * double(right) /
                    double(left + right));
    }
  }
  for (double x : res) {
    printf("%0.18lf\n", x);
  }

  return 0;
}
