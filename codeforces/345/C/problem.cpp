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

class DSU {
 public:
  explicit DSU(int n) {
    for (int i = 0; i < n; ++i) {
      par.push_back(i);
    }
  }

  int get_par(int x) { return x == par[x] ? x : par[x] = get_par(par[x]); }

  void merge(int x, int y) { par[x] = y; }

 private:
  vi par;
};

int f(int v, vi &dp, const vii &al) {
  int &res = dp[v];
  if (res >= 0) {
    return res;
  }
  res = 0;
  for (int v2 : al[v]) {
    res = max(res, 1 + f(v2, dp, al));
  }
  return res;
}

int longest_path(const vii &al) {
  int m = 0;
  vi dp(al.size(), -1);
  for (size_t v = 0; v < al.size(); ++v) {
    m = max(m, f(static_cast<int>(v), dp, al));
  }
  return m;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vii a(n, vi(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  DSU dsu(n * m);
  for (int i = 0; i < n; ++i) {
    vector<pair<int, int>> row;
    for (int j = 0; j < m; ++j) {
      row.emplace_back(a[i][j], i * m + j);
    }
    sort(all(row));
    for (int j = 1; j < m; ++j) {
      if (row[j].first == row[j - 1].first) {
        dsu.merge(row[j].second, row[j - 1].second);
      }
    }
  }
  for (int j = 0; j < m; ++j) {
    vector<pair<int, int>> col;
    for (int i = 0; i < n; ++i) {
      col.emplace_back(a[i][j], i * m + j);
    }
    sort(all(col));
    for (int i = 1; i < n; ++i) {
      if (col[i].first == col[i - 1].first) {
        dsu.merge(col[i].second, col[i - 1].second);
      }
    }
  }
  std::vector<int> roots;
  for (int i = 0; i < n * m; ++i) {
    if (i == dsu.get_par(i)) {
      roots.push_back(i);
    }
  }
  debug(roots.size());
  vii al(roots.size());
  for (int i = 0; i < n; ++i) {
    vector<pair<int, int>> row;
    for (int j = 0; j < m; ++j) {
      row.emplace_back(a[i][j], i * m + j);
    }
    sort(all(row));
    for (int j = 1; j < m; ++j) {
      if (row[j - 1].first < row[j].first) {
        al[int(std::lower_bound(all(roots), dsu.get_par(row[j].second)) -
               roots.begin())]
            .push_back(int(
                std::lower_bound(all(roots), dsu.get_par(row[j - 1].second)) -
                roots.begin()));
      }
    }
  }
  for (int j = 0; j < m; ++j) {
    vector<pair<int, int>> col;
    for (int i = 0; i < n; ++i) {
      col.emplace_back(a[i][j], i * m + j);
    }
    sort(all(col));
    for (int i = 1; i < n; ++i) {
      if (col[i - 1].first < col[i].first) {
        al[int(std::lower_bound(all(roots), dsu.get_par(col[i].second)) -
               roots.begin())]
            .push_back(int(
                std::lower_bound(all(roots), dsu.get_par(col[i - 1].second)) -
                roots.begin()));
      }
    }
  }

  // debug(al);

  vi dp(al.size(), -1);
  vii res(n, vi(m, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int r = dsu.get_par(i * m + j);
      int v = int(std::lower_bound(all(roots), r) - roots.begin());
      res[i][j] = f(v, dp, al);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << 1 + res[i][j] << " ";
    }
    cout << "\n";
  }

  return 0;
}
