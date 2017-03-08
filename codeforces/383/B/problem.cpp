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

class SetUnion {
 public:
  explicit SetUnion(const vi &weight, const vi &beauty) {
    this->weight = weight;
    this->beauty = beauty;
    for (int i = 0; i < static_cast<int>(weight.size()); ++i) {
      parent.push_back(i);
    }
  }

  void merge(int x, int y) {
    x = getPar(x);
    y = getPar(y);
    if (x == y) {
      return;
    }
    parent[x] = y;
    weight[y] += weight[x];
    weight[x] = -INF;
    beauty[y] += beauty[x];
    beauty[x] = -INF;
  }

  int getPar(int x) {
    return x == parent[x] ? x : parent[x] = getPar(parent[x]);
  }

  vector<int> weight;
  vector<int> beauty;
  vector<int> parent;
};

int solveKnapsack(const vector<vector<pii>> &options, int W) {
  vi dp(W + 1, 0);
  for (int i = 0; i < static_cast<int>(options.size()); ++i) {
    vi ndp(dp);
    for (int w = 0; w <= W; ++w) {
      for (int j = 0; j < static_cast<int>(options[i].size()); ++j) {
        int nw = w + options[i][j].first;
        if (nw <= W) {
          ndp[nw] = max(ndp[nw], dp[w] + options[i][j].second);
        }
      }
    }
    dp = ndp;
  }
  return *max_element(all(dp));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m, w;
  cin >> n >> m >> w;
  vi weight(n);
  for (int &x : weight) {
    cin >> x;
  }
  vi beauty(n);
  for (int &x : beauty) {
    cin >> x;
  }
  SetUnion groups(weight, beauty);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    groups.merge(x, y);
  }
  vector<vector<pii>> options;
  for (int i = 0; i < n; ++i) {
    if (groups.getPar(i) == i) {
      vector<pii> opt;
      opt.emplace_back(groups.weight[i], groups.beauty[i]);
      for (int j = 0; j < n; ++j) {
        if (groups.getPar(j) == i) {
          opt.emplace_back(weight[j], beauty[j]);
        }
      }
      options.push_back(opt);
    }
  }
  cout << solveKnapsack(options, w) << "\n";

  return 0;
}
