#include "sandwich-1.h"
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

struct Message {
  ll sum = 0;
  ll largest_pref = 0;
  ll largest_suf = 0;
  ll smallest_window = LLINF;

  void send_to(int node) {
    PutLL(node, sum);
    PutLL(node, largest_pref);
    PutLL(node, largest_suf);
    PutLL(node, smallest_window);
    Send(node);
  }
  static Message receive_from(int node) {
    Receive(node);
    Message m;
    m.sum = GetLL(node);
    m.largest_pref = GetLL(node);
    m.largest_suf = GetLL(node);
    m.smallest_window = GetLL(node);
    return m;
  }
};

Message f(vector<ll> seq) {
  Message m;
  for (int i = 0; i < seq.size(); ++i) {
    m.sum += seq[i];
  }
  // debug(m.sum);
  {
    ll cur_sum = 0;
    for (int i = 0; i < seq.size(); ++i) {
      cur_sum += seq[i];
      m.largest_pref = max(m.largest_pref, cur_sum);
    }
  }
  {
    ll cur_sum = 0;
    for (int i = 0; i < seq.size(); ++i) {
      cur_sum += seq[seq.size() - 1 - i];
      m.largest_suf = max(m.largest_suf, cur_sum);
    }
  }
  {
    for (ll &x : seq) {
      x *= -1;
    }
    // debug(seq);
    int j = 0;
    int i = 0;
    int n = seq.size();
    while (i < n) {
      // debug(i);
      ll cur_sum = seq[i];
      m.smallest_window = min(m.smallest_window, -cur_sum);
      j = i + 1;
      while (j < n && cur_sum + seq[j] >= 0) {
        cur_sum += seq[j];
        m.smallest_window = min(m.smallest_window, -cur_sum);
        ++j;
      }
      // debug(j);
      i = j;
      m.smallest_window = min(m.smallest_window, -cur_sum);
    }
  }
  // debug(m.smallest_window);
  return m;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n = GetN();
  int B = calc_single_processor_range_length(n);

  if (useless_node()) {
    return 0;
  }

  int from = B * my_node_id;
  int to = min(n, B + from);

  vector<ll> seq;
  for (int i = from; i < to; ++i) {
    seq.push_back(GetTaste(i));
  }
  Message m = f(seq);
  if (!is_first_node()) {
    m.send_to(0);
  } else {
    vector<Message> messages;
    messages.push_back(m);
    for (int node = 1; node < number_of_nodes; ++node) {
      messages.push_back(Message::receive_from(node));
    }
    ll res = 0;
    for (int i = 0; i <= number_of_nodes; ++i) {
      for (int j = 0; j <= number_of_nodes; ++j) {
        if (i + j > number_of_nodes) {
          continue;
        }
        ll cur = 0;
        for (int x = 0; x < i; ++x) {
          cur += messages[x].sum;
        }
        int last = number_of_nodes;
        for (int y = number_of_nodes - 1, k = 0; k < j; --y, ++k) {
          cur += messages[y].sum;
          last = y;
        }
        --last;
        // debug(last);
        if (i + j == number_of_nodes) {
        } else if (i + j + 1 == number_of_nodes) {
          cur += messages[last].sum - messages[last].smallest_window;
        } else {
          cur += messages[i].largest_pref;
          cur += messages[last].largest_suf;
        }
        res = max(res, cur);
      }
    }
    cout << res << "\n";
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
