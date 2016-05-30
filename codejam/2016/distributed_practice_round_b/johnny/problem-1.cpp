#include "johnny-1.h"
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
#define debug(x) \
  cout << "DEBUG(" << my_node_id << ")" << #x << " : " << (x) << "\n";

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

bool req(int i, int j) { return IsBetter(i, j); }

bool edge(int i, int j) { return req(i, j); }

int main() {
  std::ios_base::sync_with_stdio(false);

  int n = NumberOfCards();

  if (!is_first_node()) {
    return 0;
  } else {
    /*for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        cout << i << " ";
        if (edge(i, j)) {
          cout << " -> ";
        } else {
          cout << " <- ";
        }
        cout << j << "\n";
      }
    }*/
    vector<int> c;
    for (int i = 0; i < n; ++i) {
      c.push_back(i);
    }
    random_shuffle(all(c));
    vi outgoing(n, -1);
    while (c.size() > 1) {
      // debug(c);
      vi new_c;
      if (c.size() & 1) {
        new_c.push_back(c.back());
        c.pop_back();
      }
      for (int i = 0; i < c.size(); i += 2) {
        int x = c[i];
        int y = c[i + 1];
        if (edge(x, y)) {
          outgoing[x] = y;
          new_c.push_back(y);
        } else {
          outgoing[y] = x;
          new_c.push_back(x);
        }
      }
      c = new_c;
    }
    queue<int> Q;
    Q.push(c[0]);
    std::vector<bool> used(n);
    used[c[0]] = 1;
    // debug(c[0]);
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for (int k = 0; k < n; ++k) {
        if (used[k]) {
          continue;
        }
        if (edge(v, k)) {
          int v2 = k;
          while (v2 >= 0 && !used[v2]) {
            Q.push(v2);
            used[v2] = 1;
            v2 = outgoing[v2];
          }
        }
      }
    }
    int ans = count(all(used), true);
    if (ans == n) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << n - ans << "\n";
    }
    return 0;
  }

  int B = calc_single_processor_range_length(n);

  if (useless_node()) {
    return 0;
  }

  int from = B * my_node_id;
  int to = min(from + B, n);

  int ans = INF;
  vector<bool> bad(n, false);
  for (int i = from; i < to; ++i) {
    if (bad[i]) {
      continue;
    }
    queue<int> Q;
    Q.push(i);
    std::vector<bool> used(n);
    used[i] = 1;
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for (int k = 0; k < n; ++k) {
        if (used[k]) {
          continue;
        }
        if (req(v, k)) {
          Q.push(k);
          used[k] = 1;
        } else {
          bad[k] = true;
        }
      }
    }
    int r = std::count(all(used), true);
    ans = min(r, ans);
  }
  if (is_first_node()) {
    for (int node = 1; node < number_of_nodes; ++node) {
      Receive(node);
      ans = min(ans, GetInt(node));
    }
    if (ans == n) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << n - ans << "\n";
    }
  } else {
    PutInt(0, ans);
    Send(0);
  }

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
