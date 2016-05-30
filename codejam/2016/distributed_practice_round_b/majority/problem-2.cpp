#include "majority-2.h"
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
// cout << "DEBUG(" << my_node_id << ")" << #x << " : " << (x) << "\n";

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

struct Message {
  int value;
  int num;

  void send_to(int node) const {
    PutInt(node, value);
    PutInt(node, num);
    Send(node);
  }

  static Message receive_from(int node) {
    Receive(node);
    Message m;
    m.value = GetInt(node);
    m.num = GetInt(node);
    return m;
  }
};

ostream &operator<<(ostream &o, const Message &m) {
  o << "{";
  o << m.value << ", " << m.num;
  o << "}";
  return o;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n = GetN();
  int B = calc_single_processor_range_length(n);

  if (useless_node()) {
    return 0;
  }

  int from = my_node_id * B;
  int to = min(n, (1 + my_node_id) * B);

  Message stat;
  stat.value = -1;
  stat.num = 0;
  vi data;
  for (int i = from; i < to; ++i) {
    int x = GetVote(i);
    data.push_back(x);
    if (stat.value == x) {
      ++stat.num;
    } else {
      if (stat.num == 0) {
        stat.value = x;
        stat.num = 1;
      } else {
        --stat.num;
      }
    }
  }
  if (!is_first_node()) {
    stat.send_to(0);
  } else {
    for (int node = 1; node < number_of_nodes; ++node) {
      Message other_stat = Message::receive_from(node);
      if (stat.value == other_stat.value) {
        stat.num += other_stat.num;
      } else {
        debug(stat);
        debug(other_stat);

        if (stat.num < other_stat.num) {
          swap(stat, other_stat);
        }
        stat.num -= other_stat.num;
        assert(stat.num >= 0);
      }
    }
  }

  int candidate = stat.value;
  if (!is_first_node()) {
    Receive(0);
    candidate = GetInt(0);
  } else {
    for (int node = 1; node < number_of_nodes; ++node) {
      PutInt(node, candidate);
      Send(node);
    }
  }
  int candidate_count = std::count(all(data), candidate);
  debug(data);
  debug(candidate);
  debug(candidate_count);
  if (!is_first_node()) {
    PutInt(0, candidate_count);
    Send(0);
  } else {
    for (int node = 1; node < number_of_nodes; ++node) {
      Receive(node);
      candidate_count += GetInt(node);
    }
    if (2 * candidate_count > n) {
      cout << candidate << "\n";
    } else {
      cout << "NO WINNER\n";
    }
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
