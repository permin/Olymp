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

struct State {
  State(int x, int y, int a, int b) : x(x), y(y), a(a), b(b) {}
  int x, y;
  int a, b;

  bool operator==(const State &st) const {
    return x == st.x && y == st.y && a == st.a && b == st.b;
  }
  bool operator<(const State &st) const {
    if (x != st.x) {
      return x < st.x;
    }
    if (y != st.y) {
      return y < st.y;
    }
    if (a != st.a) {
      return a < st.a;
    }
    if (b != st.b) {
      return b < st.b;
    }
    return false;
  }
};

bool is_valid(int x, int y, int n, int m) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

bool is_valid(const State &state, int n, int m) {
  return is_valid(state.x, state.y, n, m) && is_valid(state.a, state.b, n, m);
}

bool is_fail(const State &state, const vector<string> &plan) {
  if (!is_valid(state, static_cast<int>(plan.size()),
                static_cast<int>(plan[0].size()))) {
    return false;
  }
  return plan[state.x][state.y] == 'P' || plan[state.a][state.b] == 'P';
}

int val_mod(int x, int dx, int n) { return (x + n + dx) % n; }

vector<State> neigh(const State &st, const vector<string> &plan) {
  const int n = static_cast<int>(plan.size());
  const int m = static_cast<int>(plan[0].size());
  vector<State> res;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= +1; ++dy) {
      if (dx * dx + dy * dy == 1) {
        State ns(val_mod(st.x, dx, n), val_mod(st.y, dy, m),
                 val_mod(st.a, dx, n), val_mod(st.b, dy, m));
        if (is_fail(ns, plan)) {
          continue;
        }
        if (plan[ns.x][ns.y] == 'W') {
          ns.x = st.x;
          ns.y = st.y;
        }
        if (plan[ns.a][ns.b] == 'W') {
          ns.a = st.a;
          ns.b = st.b;
        }
        if (ns == st) {
          continue;
        }
        res.emplace_back(ns);
      }
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<string> plan(n);
  for (int i = 0; i < n; ++i) {
    cin >> plan[i];
  }

  map<State, int> dist;
  State origin(-1, -1, -1, -1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (plan[i][j] == 'S') {
        if (origin.x == -1) {
          origin.x = i;
          origin.y = j;
        } else {
          origin.a = i;
          origin.b = j;
        }
      }
    }
  }

  if (origin.a == -1) {
    cout << 0;
    return 0;
  }

  queue<State> q;
  q.push(origin);
  dist[origin] = 0;
  while (!q.empty()) {
    State s = q.front();
    q.pop();
    if (s.x == s.a && s.y == s.b) {
      cout << dist[s] << "\n";
      return 0;
    }
    auto neig = neigh(s, plan);
    for (const State &ns : neig) {
      if (dist.count(ns) == 0) {
        dist[ns] = dist[s] + 1;
        q.push(ns);
      }
    }
  }
  cout << "-1\n";

  return 0;
}
