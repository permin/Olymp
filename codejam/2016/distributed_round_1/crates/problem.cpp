#include "crates.h"
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

const ll mod = 1000000007;
ll add(ll x, ll y) { return ((x % mod) + (y % mod)) % mod; }

struct Message {
  ll left = 0;
  ll right = 0;

  void sent_to(int node) const {
    PutLL(node, left);
    PutLL(node, right);
    Send(node);
  }

  static Message receive_from(int node) {
    Message m;
    Receive(node);
    m.left = GetLL(node);
    m.right = GetLL(node);
    return m;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);

  int n = GetNumStacks();
  int B = calc_single_processor_range_length(n);

  if (useless_node()) {
    return 0;
  }

  int from = B * my_node_id;
  int to = min(n, from + B);
  ll sum = 0;
  vector<ll> landscape;
  for (int i = from; i < to; ++i) {
    ll x = GetStackHeight(i + 1);
    sum += x;
    landscape.push_back(x);
  }
  ll total_sum = 0;
  std::vector<ll> actual_sums;
  if (!is_master()) {
    PutLL(master_node(), sum);
    Send(master_node());
    Receive(master_node());
    total_sum = GetLL(master_node());
  } else {
    total_sum += sum;
    actual_sums.push_back(sum);
    for (int node = 1; node < number_of_nodes; ++node) {
      Receive(node);
      ll s = GetLL(node);
      actual_sums.push_back(s);
      total_sum += s;
    }
    for (int node = 1; node < number_of_nodes; ++node) {
      PutLL(node, total_sum);
      Send(node);
    }
  }

  int bound = (int)(total_sum % n);
  ll should_be = 0;
  for (int i = from; i < to; ++i) {
    should_be += (total_sum / n);
    if (i < bound) {
      ++should_be;
    }
  }
  Message task;

  if (!is_master()) {
    PutLL(master_node(), should_be);
    Send(master_node());

    task = Message::receive_from(master_node());
  } else {
    task.left = 0;
    task.right = should_be - actual_sums[0];
    ll pref_actual_sum = actual_sums[0];
    ll pref_desired_sum = should_be;
    for (int node = 1; node < number_of_nodes; ++node) {
      Message m;
      m.left = pref_actual_sum - pref_desired_sum;
      Receive(node);
      ll s = GetLL(node);
      pref_actual_sum += actual_sums[node];
      pref_desired_sum += s;
      m.right = pref_desired_sum - pref_actual_sum;
      if (node + 1 == total_sum) {
        // assert(m.right == 0);
      }
      m.sent_to(node);
    }
  }

  ll crates = task.left;
  ll moves = 0;
  for (int i = 0; i < landscape.size(); ++i) {
    moves = add(moves, abs(crates));
    crates += landscape[i];
    int j = i + from;
    crates -= (total_sum / n);
    if (j < bound) {
      crates -= 1;
    }
  }
  // moves = add(moves, abs(crates));
  // assert(crates == -task.right);
  if (!is_master()) {
    PutLL(master_node(), moves);
    Send(master_node());
  } else {
    for (int node = 1; node < number_of_nodes; ++node) {
      Receive(node);
      moves = add(moves, GetLL(node));
    }
    cout << moves << "\n";
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
