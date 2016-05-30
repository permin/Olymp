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
const int INF = std::numeric_limits<int>::max() / 2;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

vii distances(const vii &al) {
  size_t n = al.size();
  vii res;
  for (size_t s = 0; s < n; ++s) {
    vi dist(n, INF);
    dist[s] = 0;
    queue<int> Q;
    Q.push(static_cast<int>(s));
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for (int v2 : al[v]) {
        if (dist[v2] == INF) {
          dist[v2] = dist[v] + 1;
          Q.push(v2);
        }
      }
    }
    res.emplace_back(std::move(dist));
  }
  return res;
}

int arg_max(const vi &ar, int a = -1, int b = -1, int c = -1) {
  int i = -1;
  for (int j = 0; j < static_cast<int>(ar.size()); ++j) {
    if (j == a || j == b || j == c) {
      continue;
    }
    if (ar[j] >= INF) {
      continue;
    }
    if (i == -1 || ar[j] > ar[i]) {
      i = j;
    }
  }
  return i;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vii al(n);
  vii tal(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    if (a == b) {
      continue;
    }
    al[a].push_back(b);
    tal[b].push_back(a);
  }

  vii dist_from = distances(al);
  vii dist_to = distances(tal);

  vii best_3_prev(n);
  vii best_3_next(n);
  for (int s = 0; s < n; ++s) {
    best_3_next[s].push_back(arg_max(dist_from[s]));
    best_3_next[s].push_back(arg_max(dist_from[s], best_3_next[s][0]));
    best_3_next[s].push_back(
        arg_max(dist_from[s], best_3_next[s][0], best_3_next[s][1]));

    best_3_prev[s].push_back(arg_max(dist_to[s]));
    best_3_prev[s].push_back(arg_max(dist_to[s], best_3_prev[s][0]));
    best_3_prev[s].push_back(
        arg_max(dist_to[s], best_3_prev[s][0], best_3_prev[s][1]));
  }
  int A, B, C, D;
  int res = -1;
  A = B = C = D = -2;

  for (int b = 0; b < n; ++b) {
    for (int c = 0; c < n; ++c) {
      if (c == b) {
        continue;
      }
      if (dist_from[b][c] >= INF) {
        continue;
      }
      for (int a : best_3_prev[b]) {
        if (a == -1) {
          continue;
        }
        for (int d : best_3_next[c]) {
          if (d == -1) {
            continue;
          }
          if (a == d || a == b || a == c || b == d || c == d) {
            continue;
          }
          if (res < dist_from[a][b] + dist_from[b][c] + dist_from[c][d]) {
            res = dist_from[a][b] + dist_from[b][c] + dist_from[c][d];
            A = a;
            B = b;
            C = c;
            D = d;
          }
        }
      }
    }
  }
  ++A;
  ++B;
  ++C;
  ++D;
  cout << A << " " << B << " " << C << " " << D << "\n";
  debug(res);

  return 0;
}
