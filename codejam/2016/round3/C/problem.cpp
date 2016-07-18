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

double sqr(int x) { return 1.0 * x * x; }

double dist(int x, int y, int z, int a, int b, int c) {
  return sqrt(sqr(x - a) + sqr(y - b) + sqr(z - c));
}

void solve_test() {
  int n;
  int s;
  cin >> n >> s;
  vector<int> x(n);
  vector<int> y(n);
  vector<int> z(n);
  for (int i = 0; i < n; ++i) {
    double _;
    cin >> x[i] >> y[i] >> z[i];
    cin >> _ >> _ >> _;
  }
  vector<bool> alive(n, true);
  vector<double> min_dist(n, 1e40);
  min_dist[0] = 0;
  for (int it = 0; it < n; ++it) {
    int v = -1;
    for (int i = 0; i < n; ++i) {
      if (alive[i] && (v == -1 || min_dist[v] > min_dist[i])) {
        v = i;
      }
    }
    assert(alive[v]);
    alive[v] = false;
    for (int i = 0; i < n; ++i) {
      min_dist[i] =
          min(min_dist[i],
              max(min_dist[v], dist(x[i], y[i], z[i], x[v], y[v], z[v])));
    }
  }
  printf("%0.18lf\n", min_dist[n - 1]);
}

void solve_test2() {
  int n;
  int s;
  cin >> n >> s;
  vector<int> x(n);
  vector<int> y(n);
  vector<int> z(n);
  for (int i = 0; i < n; ++i) {
    double _;
    cin >> x[i] >> y[i] >> z[i];
    cin >> _;
    assert(fabs(_) < EPS);
    cin >> _;
    assert(fabs(_) < EPS);
    cin >> _;
    assert(fabs(_) < EPS);
  }

  double lower = 0;
  double upper = 1e10;
  for (int it = 0; it < 100; ++it) {
    double med = 0.5 * (lower + upper);
    vector<bool> used(n);
    queue<int> Q;
    Q.push(0);
    used[0] = 1;
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for (int i = 0; i < n; ++i) {
        if (!used[i] && dist(x[i], y[i], z[i], x[v], y[v], z[v]) <= med) {
          used[i] = true;
          Q.push(i);
        }
      }
    }
    if (used[n - 1]) {
      upper = med;
    } else {
      lower = med;
    }
  }
  printf("%0.18lf\n", lower);
}

int main() {
  int tests;
  cin >> tests;
  for (int test = 0; test < tests; ++test) {
    cout << "Case #" << test + 1 << ": ";
    solve_test2();
  }

  return 0;
}
