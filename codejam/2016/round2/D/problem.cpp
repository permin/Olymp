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

typedef vector<vector<bool>> BoolMatrix;

template <class It>
bool go(It begin, It end, int machine_free, const BoolMatrix &can) {
  if (begin == end) {
    return true;
  }
  int n = (int)can.size();
  bool ok = 1;
  int op = 0;
  for (int m = 0; m < n; ++m) {
    if (machine_free & (1 << m)) {
      if (can[*begin][m]) {
        op += 1;
        ok = ok && go(std::next(begin), end, machine_free ^ (1 << m), can);
      }
    }
  }
  return ok && op > 0;
}

bool test(const BoolMatrix &can) {
  int n = (int)can.size();
  vector<int> p;
  for (int i = 0; i < n; ++i) {
    p.push_back(i);
  }
  bool ok = true;
  do {
    int machine_free = (1 << n) - 1;
    ok = ok && go(p.begin(), p.end(), machine_free, can);
  } while (next_permutation(all(p)));
  return ok;
}

int solve_large(const BoolMatrix &can_operate) {
  int n = (int)can_operate.size();
  vector<int> people(n);
  vector<int> machines(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (can_operate[i][j]) {
        people[j] |= 1 << i;
        machines[i] |= 1 << j;
      }
    }
  }
  int ans = 0;
  debug(people);
  debug(machines);
  vector<int> P(1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      if (i & (1 << j)) {
        P[i] = P[i ^ (1 << j)] | people[j];
        break;
      }
    }
  }
  debug(P);
  for (int looser = 0; looser < n; ++looser) {
    vector<int> with_violation(1 << n);
    for (int i = 0; i < (1 << n); ++i) {
      int mask = P[i];
      if (mask & (1 << looser)) {
        mask ^= 1 << looser;
      }
      with_violation[i] = __builtin_popcount(mask) < __builtin_popcount(i);
    }

    debug(with_violation);
    int c = INF;  // n - __builtin_popcount(machines[looser]);
    for (int mask = 0; mask < (1 << n); ++mask) {
      if (mask && with_violation[mask] &&
          ((mask & machines[looser]) == machines[looser])) {
        c = min(c, __builtin_popcount(mask ^ machines[looser]));
      }
    }
    ans += c;
  }
  return ans;
}

int solve_small(const BoolMatrix &can_operate) {
  int n = (int)can_operate.size();
  int ans = n * n;
  int can_mask = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      can_mask |= (can_operate[i][j] << (i * n + j));
    }
  }
  for (int mask = 0; mask < (1 << (n * n)); ++mask) {
    int new_can_mask = mask | can_mask;
    int lesson = new_can_mask ^ can_mask;
    int cur = __builtin_popcount(lesson);

    if (cur > ans) continue;
    BoolMatrix new_can(n, vector<bool>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        new_can[i][j] = new_can_mask & (1 << (i * n + j));
      }
    }
    if (test(new_can)) {
      ans = min(ans, cur);
    }
  }
  return ans;
}

void solve_test() {
  int n;
  cin >> n;
  vector<vector<bool>> can_operate(n, vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j) {
      if (s[j] == '1') can_operate[i][j] = 1;
    }
  }
  cout << solve_large(can_operate) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; ++t) {
    cout << "Case #" << t + 1 << ": ";
    solve_test();
  }
  return 0;
}
