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
    if (!f)
      o << ", ";
    if (IsIterable__<decltype(x)>::value)
      o << "\n";
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

double calculate_sum(int bound, const vi &c) {
  int cycle_len = 0;
  for (int x : c) {
    if (cycle_len > bound)
      break;
    cycle_len += x;
  }
  int num_cycles = bound / cycle_len;
  int rem_length = bound - num_cycles * cycle_len;
  double sum = 0.0;
  for (int x : c) {
    sum += 0.5 * num_cycles * x * x;
  }
  {
    size_t i = 0;
    while (c[i] <= rem_length) {
      sum += 0.5 * c[i] * c[i];
      rem_length -= c[i];
      ++i;
    }
    sum += 0.5 * rem_length * rem_length;
  }
  return sum;
}

double solve_dummy(int a, int b, const vi &c) {
  double sum = 0.0;
  size_t j = 0;
  int cur_length = 0;
  for (int i = 0; i < b; ++i) {
    if (cur_length == c[j]) {
      ++j;
      if (j == c.size())
        j = 0;
      cur_length = 0;
    }
    if (i >= a) {
      sum += cur_length + 0.5;
    }
    ++cur_length;
  }
  return sum / (b - a);
}

double solve(int a, int b, const vi &c) {
  double res = 1.0 / (b - a) * (calculate_sum(b, c) - calculate_sum(a, c));
  return res;
}

void ss() {
  for (int t = 0; t < 1000 * 1000; ++t) {
    const int M = 1000;
    int a = rand() % M;
    int b = rand() % M;
    if (a == b)
      continue;
    if (a > b)
      swap(a, b);
    int n = rand() % 40;
    ++n;
    vi c(n);
    int m = rand() % (3 * M / 2);
    ++m;
    for (int i = 0; i < n; ++i) {
      c[i] = rand() % m;
      ++c[i];
    }
    if (fabs(solve(a, b, c) - solve_dummy(a, b, c)) > EPS) {
      debug(solve(a, b, c));
      debug(solve_dummy(a, b, c));
      debug(a);
      debug(b);
      debug(c);
    } else {
    }
  }
  debug("done!");
}

void solve_test() {
  int n;
  cin >> n;
  vi c(n);
  int a, b;
  cin >> a >> b;
  for (int &x : c) {
    cin >> x;
  }
  if (b < 1000 * 1000) {
    if (fabs(solve(a, b, c) - solve_dummy(a, b, c)) > EPS) {
      debug(solve(a, b, c));
      debug(solve_dummy(a, b, c));
      debug(a);
      debug(b);
      debug(c);
    }
  }
  printf("%0.18lf", solve(a, b, c));
}

int main() {
  if (0) {
    ss();
    return 0;
  }
  size_t test_number = 0;
  cin >> test_number;
  for (size_t test_index = 0; test_index < test_number; ++test_index) {
    cout << "Case #" << test_index + 1 << ": ";
    solve_test();
    cout << "\n";
  }
  return 0;
}
