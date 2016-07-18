#include "asteroids.h"
#include <message.h>

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
#define debug(x) cerr << #x << " : " << (x) << "\n";

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

int number_of_nodes = NumberOfNodes();
int my_node_id = MyNodeId();

bool is_first_node() { return my_node_id == 0; }
bool is_master() { return is_first_node(); }
int master_node() { return 0; }

bool is_last_node() { return my_node_id + 1 == number_of_nodes; }
bool useless_node() { return my_node_id >= number_of_nodes; }

int next_node() { return my_node_id + 1; }
int prev_node() { return my_node_id - 1; }

// Determines B such that i-th processor should process
// range [B * i, min(sequence_length, B * (i+1))
// It is guaranteed that all ranges are non-empty
// SIDE EFFECT: May decrease number_of_nodes!
int calc_single_processor_range_length(int sequence_length) {
  int B = (sequence_length + number_of_nodes - 1) / number_of_nodes;
  int new_number_of_nodes = (sequence_length + B - 1) / B;
  assert(new_number_of_nodes <= number_of_nodes);
  number_of_nodes = new_number_of_nodes;
  return B;
}

int score(const vector<string> &plan, int x, int y) {
  assert(plan[y][x] != '#');
  assert(plan[y][x] != '?');

  return int(plan[y][x] - '0');
}

int solve(int x, int y, int can, viii &dp, const vector<string> &plan) {
  int n = (int)plan.size();
  int m = (int)plan[0].size();
  int &res = dp[y][x][can];
  if (res >= -1) {
    return res;
  }
  res = -1;
  if (y == n - 1) {
    res = 0;
  }
  if (can) {
    for (int dx : {-1, +1}) {
      int nx = x + dx;
      if (nx < 0 || nx >= m || plan[y][nx] == '#') {
        continue;
      }
      int suf = solve(nx, y, 0, dp, plan);
      if (suf >= 0) {
        res = max(res, suf + score(plan, nx, y));
      }
    }
    int suf = solve(x, y, 0, dp, plan);
    if (suf >= 0) {
      res = max(res, suf);
    }
  }
  if (y < n - 1 && plan[y + 1][x] != '#') {
    int suf = solve(x, y + 1, 1, dp, plan);
    if (suf >= 0) {
      res = max(res, suf + score(plan, x, y + 1));
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  // int n = NumberOfFiles();
  // int k = MaxDistance();
  // int B = calc_single_processor_range_length(n);

  number_of_nodes = 1;
  if (useless_node()) {
    return 0;
  }
  vector<string> plan(GetHeight(), string(GetWidth(), '?'));
  int n = GetHeight();
  int m = GetWidth();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      plan[i][j] = GetPosition(i, j);
    }
  }
  vector<vector<vector<int>>> dist(n, vii(m, vi(2, -2)));
  int res = -1;
  for (int i = 0; i < m; ++i) {
    int x = i;
    int y = 0;
    if (plan[y][x] != '#') {
      int cur = solve(x, y, 1, dist, plan);
      if (cur >= 0) {
        res = max(res, cur + score(plan, x, y));
      }
    }
  }
  cout << res << "\n";

  return 0;
}

/*long long sum = 0LL;
for (long long pos = MyNodeId(); pos < GetN(); pos += NumberOfNodes()) {
  sum += GetTaste(pos);
}
if (MyNodeId() > 0) {
  Receive(MyNodeId() - 1);
  sum += GetLL(MyNodeId() - 1);
}
if (MyNodeId() < NumberOfNodes() - 1) {
  PutLL(MyNodeId() + 1, sum);
  Send(MyNodeId() + 1);
} else {
  cout << sum << "\n";
}
// HELLO*/
