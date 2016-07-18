#include "again.h"
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

const int mod = 1000000007;

int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int sub(int x, int y) {
  if (y == 0) {
    return x;
  } else {
    return add(x, mod - y);
  }
}

int mul(int x, int y) { return int((1LL * x * y) % mod); }

struct Message {
  int sum = 0;
  int mod_sum[20];
  Message() {
    for (int i = 0; i < number_of_nodes; ++i) {
      mod_sum[i] = 0;
    }
  }

  static Message receive_from(int node) {
    Receive(node);
    Message m;
    m.sum = GetInt(node);
    for (int i = 0; i < number_of_nodes; ++i) {
      m.mod_sum[i] = GetInt(node);
    }
    return m;
  }
  void send_to(int node) {
    PutInt(node, sum);
    for (int i = 0; i < number_of_nodes; ++i) {
      PutInt(node, mod_sum[i]);
    }
    Send(node);
  }
};

Message combine(Message m1, const Message &m2) {
  m1.sum = add(m1.sum, m2.sum);
  for (int i = 0; i < number_of_nodes; ++i) {
    m1.mod_sum[i] = add(m1.mod_sum[i], m2.mod_sum[i]);
  }
  return m1;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  // int n = NumberOfFiles();
  // int k = MaxDistance();
  // int B = calc_single_processor_range_length(n);

  Message m_a;
  Message m_b;
  int n = GetN();
  int B = (n + number_of_nodes + 1) / number_of_nodes;
  int from = B * my_node_id;
  int to = min(n, from + B);
  for (int i = from; i < to; ++i) {
    m_a.sum = add(m_a.sum, GetA(i));
    m_a.mod_sum[i % number_of_nodes] =
        add(m_a.mod_sum[i % number_of_nodes], GetA(i));
    m_b.sum = add(m_b.sum, GetB(i));
    m_b.mod_sum[i % number_of_nodes] =
        add(m_b.mod_sum[i % number_of_nodes], GetB(i));
  }

  if (is_master()) {
    for (int node = 1; node < number_of_nodes; ++node) {
      m_a = combine(m_a, Message::receive_from(node));
      m_b = combine(m_b, Message::receive_from(node));
    }
    int res = 0;
    res = mul(m_a.sum, m_b.sum);
    for (int i = 0; i < number_of_nodes; ++i) {
      res = sub(res, mul(m_a.mod_sum[i],
                         m_b.mod_sum[(number_of_nodes - i) % number_of_nodes]));
    }
    cout << res << "\n";

  } else {
    m_a.send_to(master_node());
    m_b.send_to(master_node());
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
