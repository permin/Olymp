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

vector<bool> is_tree;
vi all_trees;
size_t k;
vii edge_id;
viii transitions;

void add_tree(const vi &prufer) {
  vi deg(k, 1);
  int edges = 0;
  for (int v : prufer) {
    ++deg[v];
  }
  for (int v : prufer) {
    for (int v2 = 0; v2 < static_cast<int>(k); ++v2) {
      if (deg[v2] == 1) {
        edges |= (1 << edge_id[v2][v]);
        --deg[v];
        --deg[v2];
        break;
      }
    }
  }
  int v1 = static_cast<int>(std::find(all(deg), 1) - deg.begin());
  int v2 = (static_cast<int>(k) - 1) -
           int(std::find(deg.rbegin(), deg.rend(), 1) - deg.rbegin());
  assert(v1 != v2);
  edges |= (1 << edge_id[v2][v1]);
  --deg[v2];
  --deg[v1];
  assert(count(all(deg), 1) == 0);
  is_tree[edges] = 1;
  all_trees.push_back(edges);
}

void go(vi &prufer) {
  if (prufer.size() + 2 == k) {
    add_tree(prufer);
    return;
  }
  for (int i = 0; i < static_cast<int>(k); ++i) {
    prufer.push_back(i);
    go(prufer);
    prufer.pop_back();
  }
}

void init() {
  edge_id.assign(k, vi(k, -1));
  int i = 0;
  for (size_t v = 0; v < k; ++v) {
    for (size_t v2 = 0; v2 < v; ++v2) {
      edge_id[v][v2] = edge_id[v2][v] = i;
      ++i;
    }
  }

  is_tree.assign(k * k, 0);
  vi prufer;
  go(prufer);

  transitions.assign(all_trees.size(), vii(k));
  size_t max_len = 0;
  for (size_t i = 0; i < all_trees.size(); ++i) {
    for (size_t v = 0; v < k; ++v) {
      int subset = all_trees[i];
      for (size_t v2 = 0; v2 < k; ++v2) {
        if ((v != v2) && (subset & (1 << edge_id[v2][v]))) {
          subset ^= (1 << edge_id[v2][v]);
        }
      }
      debug(all_trees[i]);
      debug(v);
      debug(subset);
      for (size_t j = 0; j < all_trees.size(); ++j) {
        if ((all_trees[j] | subset) == all_trees[j]) {
          debug(j);
          transitions[i][v].push_back((int)j);
        }
      }
      max_len += transitions[i][v].size();
    }
  }
  debug(1.0 * max_len / all_trees.size() / k);
}

const int mod = 1000 * 1000 * 1000 + 7;

int add(int x, int y) { return (x + y) % mod; }
int mul(int x, int y) { return (1LL * x * y) % mod; }

// void count_spanning_tree(int bag_id, int edges_in_bag,
//                         const vii &bag_connections, const vii &bags_content)
//                         {}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n >> k;
  ++k;
  init();
  debug(all_trees.size());
  --k;
  debug(all_trees.at(1321321));
  if (n == (int)k) {
    std::array<int, 5> ans = {1, 1, 3, 16, 125};
    cout << ans[n - 1] << "\n";
    return 0;
  };

  vii bags;
  vector<vector<pii>> al(n);
  map<vi, int> stored_in_bag;
  map<vi, int> remove_bertex;
  for (int i = 0; i < n - (int)k; ++i) {
    vi b;
    for (size_t j = 0; j < k; ++j) {
      int x;
      cin >> x;
      --x;
      b.push_back(x);
    }
    size_t id = bags.size();
    if (stored_in_bag.count(b) == 1) {
      size_t id2 = stored_in_bag[b];
      al[id].emplace_back(id2, remove_bertex[b]);
    }
    b.push_back(i + k);
    for (size_t j = 0; j < b.size(); ++j) {
      vi c(b);
      c.erase(c.begin() + j);
      stored_in_bag[c] = id;
      remove_bertex[c] = j;
    }
    bags.emplace_back(b);
  }
  // int res = 0;

  return 0;
}
