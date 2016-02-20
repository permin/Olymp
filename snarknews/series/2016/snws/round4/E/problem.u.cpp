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

struct Edge {
  int target;
  int cap;
  int backEdge;
  int flow = 0;
};

ostream &operator<<(ostream &o, const Edge &e) {
  o << "{";
  o << "to = " << e.target << " cap = " << e.cap << " flow = " << e.flow << "";
  o << "}";
  return o;
}

void addEdge(vector<vector<Edge>> &al, int source, int target, int c) {
  Edge e, eBack;
  e.target = target;
  e.cap = c;
  e.flow = 0;

  eBack.target = source;
  eBack.cap = 0;
  eBack.flow = 0;

  e.backEdge = (int)al[target].size();
  eBack.backEdge = (int)al[source].size();
  al[source].push_back(e);
  al[target].push_back(eBack);
}

int maxFlow(vector<vector<Edge>> &al, int source, int sink, int &is_unique) {
  int flow = 0;
  int n = (int)al.size();
  bool special_it = false;
  while (true) {
    vi dist(n, INF);
    vi prev(n, -1);
    vi incEdge(n, -1);
    dist[source] = 0;
    queue<int> Q;
    Q.push(source);
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      std::vector<size_t> perm;
      for (size_t i = 0; i < al[v].size(); ++i) {
        perm.push_back(i);
      }
      random_shuffle(all(perm));
      for (size_t i : perm) {
        // for (const Edge &e : al[v]) {
        const Edge &e = al[v][i];
        if (e.cap > 0 || (e.cap >= 0 && special_it)) {
          int v2 = e.target;
          if (dist[v2] == INF) {
            dist[v2] = dist[v] + 1;
            Q.push(v2);
            incEdge[v2] = static_cast<int>(i);
            prev[v2] = v;
          }
        }
        //++i;
      }
    }
    if (special_it) {
      if (dist[sink] == INF) {
        is_unique = 1;
      } else {
        is_unique = 0;
      }
      break;
    }
    if (dist[sink] == INF) {
      special_it = 1;
      continue;
    }

    int cur = sink;
    while (cur != source) {
      // v -> v2
      int v = prev[cur];
      int v2 = cur;

      Edge &e = al[v][incEdge[v2]];
      e.cap -= 1;
      assert(e.cap >= 0);
      e.flow += 1;
      al[v2][e.backEdge].cap += 1;
      al[v2][e.backEdge].flow -= 1;

      cur = v;
    }
    flow += 1;
  }
  return flow;
}

vii doit(vector<vector<Edge>> net, int source, int sink, int n, int m,
         int total, int &is_unique) {
  vii am(n, vi(m, -1));

  if (maxFlow(net, source, sink, is_unique) != total) {
    return am;
  }

  for (int i = 0; i < n; ++i) {
    for (const Edge &e : net[i]) {
      int c = e.target - n;
      if (0 <= c && c < m) {
        am[i][c] = e.flow;
      }
    }
  }
  return am;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, m, k;
  cin >> n >> m >> k;
  vi cols(n);
  vi rows(m);
  int total = 0;
  int total2 = 0;
  for (int i = 0; i < n; ++i) {
    cin >> cols[i];
    total += cols[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> rows[i];
    total2 += rows[i];
  }
  if (total != total2) {
    cout << "Good Morning\n";
    return 0;
  }

  int source = n + m;
  int sink = source + 1;
  vector<vector<Edge>> net(sink + 1);
  for (int i = 0; i < n; ++i) {
    addEdge(net, source, i, cols[i]);
  }
  for (int i = 0; i < m; ++i) {
    addEdge(net, n + i, sink, rows[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      addEdge(net, i, n + j, k);
    }
  }

  int is_unique;
  auto ans = doit(net, source, sink, n, m, total, is_unique);

  debug(ans);
  if (!is_unique) {
    cout << "Multiple Maps\n";
  } else {
    if (ans[0][0] == -1) {
      cout << "Good Morning\n";
    } else {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          cout << ans[i][j] << " ";
        }
        cout << "\n";
      }
    }
  }

  return 0;
}
