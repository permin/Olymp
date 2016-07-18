#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
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

int R(size_t n) { return rand() % (int)n; }

double C(int n, int k) {
  double r = 1.0;
  for (int i = 1; i <= k; ++i) {
    r *= n - i + 1;
    r /= i;
  }
  return r;
}

double f(int v, const vii &al, vector<double> &w, vi &subtree_size) {
  double &res = w[v];
  if (res >= 0) {
    return res;
  }
  res = 0;
  subtree_size[v] = 1;
  if (al[v].empty()) {
    res = 1;
  } else {
    res = 1;
    for (int v2 : al[v]) {
      res *= f(v2, al, w, subtree_size);
      subtree_size[v] += subtree_size[v2];
    }
    int rem = subtree_size[v] - 1;
    for (int v2 : al[v]) {
      res *= C(rem, (int)subtree_size[v2]);
      rem -= subtree_size[v2];
    }
  }
  return res;
}

vector<double> get_weights(const vii &al) {
  int n = (int)al.size();
  vector<double> res(n, -1.0);
  vi s(n);
  for (int i = 0; i < n; ++i) {
    f(i, al, res, s);
  }
  debug(s);
  return res;
}

int choose(const vi &can, const vector<double> &w) {
  std::vector<double> ps;
  for (int i = 0; i < (int)can.size(); ++i) {
    ps.push_back((ps.empty() ? 0.0 : ps.back()) + w[can[i]]);
  }
  double p = ps.back() * rand() / RAND_MAX;

  return int(std::upper_bound(all(ps), p) - ps.begin());
}

void solve_test() {
  int n;
  cin >> n;
  vii al(n + 1);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    if (x == 0) {
      al[n].push_back(i);
    } else {
      al[x - 1].push_back(i);
    }
  }
  string alpha;
  cin >> alpha;
  int m;
  cin >> m;
  vector<string> good(m);
  for (int i = 0; i < m; ++i) {
    cin >> good[i];
  }
  double ans[5];
  const int S1 = 1 << 16;
  vector<int> sample(S1);
  vector<double> weights = get_weights(al);
  debug(weights);

  const int M = 1000 * 1000;
  for (int it = 0; it < M; ++it) {
    int counters[5];
    for (int i = 0; i < m; ++i) {
      counters[i] = 0;
    }

    vi can = {n};
    for (int a = 0; a < n + 1; ++a) {
      bool opt = false;
      for (int j = 0; j < m; ++j) {
        if (counters[j] != (int)good[j].size()) {
          opt = true;
        }
      }
      if (!opt) {
        break;
      }
      int x = choose(can, weights);
      int v = can[x];
      swap(can.back(), can[x]);
      can.pop_back();
      can.insert(can.end(), all(al[v]));
      // std::copy(all(al[v]), std::back_inserter(can));
      char ch = alpha[v];
      for (int j = 0; j < m; ++j) {
        if (counters[j] != (int)good[j].size()) {
          if (good[j][counters[j]] == ch) {
            ++counters[j];
          } else {
            counters[j] = 0;
          }
        }
      }
    }
    for (int i = 0; i < m; ++i) {
      if (counters[i] == (int)good[i].size()) {
        ans[i] += 1;
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    printf(" %0.4lf ", ans[i] / M);
  }
  printf("\n");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int test = 0; test < tests; ++test) {
    cout << "Case #" << test + 1 << ": ";
    solve_test();
  }

  return 0;
}
