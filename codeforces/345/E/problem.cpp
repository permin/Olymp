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

const int maxN = 5 * 100 * 1000 + 23;
int depth[maxN];
int subtree_size[maxN];
int parent[maxN];
int heavy_child[maxN];
int t_in[maxN];
int t_out[maxN];
int global_t;

struct Edge {
  int source;
  int target;
};

int get_depth(const Edge &e) { return min(depth[e.source], depth[e.target]); }

struct Block {
  std::set<Edge> edges;
  int parent;
};

bool operator<(const Edge &e1, const Edge &e2) {
  return get_depth(e1) < get_depth(e2);
}

void dfs(int v, const vii &al, int p = -1, int d = 0) {
  ++global_t;
  t_in[v] = global_t;
  depth[v] = d;
  subtree_size[v] = 1;
  parent[v] = p;
  heavy_child[v] = -1;
  for (int v2 : al[v]) {
    if (v2 == p) {
      continue;
    }
    dfs(v2, al, v, d + 1);
    subtree_size[v] += subtree_size[v2];
  }
  for (int v2 : al[v]) {
    if (v2 == p) {
      continue;
    }
    if (subtree_size[v2] * 2 >= subtree_size[v]) {
      heavy_child[v] = v2;
    }
  }
  t_out[v] = global_t;
}

std::vector<Block> blocks;
int block_id[maxN];
set<pii> good_edges;

/*void df2(int v, const vii &al, int p = -1) {
  if (heavy_child[v] != -1) {
    if (p == -1 || heavy_child[p] != v) {
      Block block;
      block.parent = v;
      int cur = v;
      while (heavy_child[cur] != -1) {
        int a = cur;
        int b = heavy_child[cur];
        if (a > b) {
          swap(a, b);
        }
        block_id[a] = block_id[b] = blocks.size();
        if (good_edges.count(pii(a, b)) == 0) {
          block.edges.insert(Edge{a, b});
        }
        cur = heavy_child[cur];
      }
      blocks.push_back(block);
    }
  }
}*/

bool is_an(int pred, int anc) {
  return t_in[pred] <= t_in[anc] && t_out[anc] <= t_out[pred];
}

int dp[20][maxN];

int get_lca(int x, int y) {
  if (is_an(x, y)) {
    return x;
  }
  if (is_an(y, x)) {
    return y;
  }
  for (int k = 19; k >= 0; --k) {
    if (!is_an(dp[k][x], y)) {
      x = dp[k][x];
    }
  }
  x = dp[0][x];
  assert(is_an(x, y));
  return x;
}

void report(int x, int y, int a, int b) {
  cout << x + 1 << " ";
  cout << y + 1 << " ";
  cout << a + 1 << " ";
  cout << b + 1 << " ";
  cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vii origin(n);
  set<pii> origin_edges;
  for (int i = 0; i < n; ++i) {
    block_id[i] = -1;
  }
  for (int i = 0; i + 1 < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    origin[a].push_back(b);
    origin[b].push_back(a);
    if (a > b) {
      swap(a, b);
    }
    origin_edges.emplace(a, b);
  }
  std::vector<pii> to_process;
  for (int i = 0; i + 1 < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    if (a > b) swap(a, b);
    good_edges.insert(pii(a, b));
    if (origin_edges.count(pii(a, b)) == 0) {
      to_process.push_back(pii(a, b));
    }
  }
  dfs(0, origin);
  for (int v = 0; v < n; ++v) {
    if (heavy_child[v] != -1) {
      int p = parent[v];
      if (p == -1 || heavy_child[p] != v) {
        Block block;
        block.parent = v;
        int cur = v;
        while (heavy_child[cur] != -1) {
          int a = cur;
          int b = heavy_child[cur];
          if (a > b) {
            swap(a, b);
          }
          block_id[a] = block_id[b] = static_cast<int>(blocks.size());
          if (good_edges.count(pii(a, b)) == 0) {
            block.edges.insert(Edge{a, b});
          }
          cur = heavy_child[cur];
        }
        blocks.push_back(block);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    dp[0][i] = parent[i];
  }
  dp[0][0] = 0;
  for (int k = 1; k < 20; ++k) {
    for (int i = 0; i < n; ++i) {
      dp[k][i] = dp[k - 1][dp[k - 1][i]];
    }
  }
  cout << to_process.size() << "\n";
  for (pii new_edge : to_process) {
    int x = new_edge.first;
    int y = new_edge.second;
    // debug(x);
    // debug(y);
    int lca = get_lca(new_edge.first, new_edge.second);
    // debug(lca);
    bool done = 0;
    for (int z : {x, y}) {
      if (done) {
        break;
      }
      for (;;) {
        if (z == lca) {
          break;
        }
        // debug(block_id[z]);
        if (block_id[z] == -1 || blocks[block_id[z]].parent == z) {
          int a = z;
          int b = parent[z];
          if (a > b) swap(a, b);
          if (good_edges.count(pii(a, b)) == 0 &&
              origin_edges.count(pii(a, b)) == 1) {
            report(a, b, x, y);
            origin_edges.erase(pii(a, b));
            done = 1;
            break;
          }
          z = parent[z];
        } else {
          // debug(blocks[block_id[z]].edges.size());
          // last less < z
          auto it = blocks[block_id[z]].edges.lower_bound(Edge{z, z});
          // debug(it->source);
          // debug(it->target);
          // debug(it == blocks[block_id[z]].edges.begin());
          // debug((get_depth(*std::prev(it)) < depth[lca]));
          if (it == blocks[block_id[z]].edges.begin() ||
              (get_depth(*std::prev(it)) < depth[lca])) {
            z = blocks[block_id[z]].parent;
            if (depth[z] <= depth[lca]) {
              break;
            }
          } else {
            report(std::prev(it)->source, std::prev(it)->target, x, y);
            blocks[block_id[z]].edges.erase(std::prev(it));
            done = 1;
            break;
          }
        }
      }
    }
    assert(done);
  }

  return 0;
}
