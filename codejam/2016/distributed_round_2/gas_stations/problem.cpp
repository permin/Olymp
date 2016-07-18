#include "gas_stations.h"
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

template <class T>
ostream &operator<<(ostream &o, const multiset<T> &v) {
  o << "{";
  O__(o, v);
  o << "}";
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

struct Stack {
  int top() const { return data.top().first; }
  void pop() { data.pop(); }
  int min() const {
    if (data.empty()) {
      return INF;
    }
    return data.top().second;
  }

  void push(int x) { data.push(pii(x, std::min(x, this->min()))); }
  void clear() {
    while (!data.empty()) {
      data.pop();
    }
  }

  bool empty() { return data.empty(); }
  std::stack<pii> data;
};

struct Queue {
  Stack head;
  Stack tail;

  void pop() {
    r();
    head.pop();
  }
  int top() {
    r();
    return head.top();
  }

  int min() { return std::min(head.min(), tail.min()); }
  void push(int x) { tail.push(x); }

  void r() {
    if (head.empty()) {
      while (!tail.empty()) {
        int x = tail.top();
        tail.pop();
        head.push(x);
      }
    }
  }
  void clear() {
    head.clear();
    tail.clear();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);

  int n = GetNumKms();
  int k = GetTankSize();
  int B = calc_single_processor_range_length(n);
  if (useless_node()) {
    return 0;
  }

  int from = B * my_node_id;
  int to = min(from + B, n);
  ll min_value_ = INF;
  for (int i = from; i < to; ++i) {
    min_value_ = min(min_value_, GetGasPrice(i));
  }
  for (int node = 0; node < number_of_nodes; ++node) {
    if (node != my_node_id) {
      PutLL(node, min_value_);
      Send(node);
    }
  }
  std::vector<ll> min_value_per_seg(number_of_nodes);
  for (int node = 0; node < number_of_nodes; ++node) {
    if (node == my_node_id) {
      min_value_per_seg[node] = min_value_;
    } else {
      Receive(node);
      min_value_per_seg[node] = GetLL(node);
    }
  }

  // multiset<int> prices;
  Queue Q;
  int cached_bucket = -1;
  ll min2 = LLINF;
  ll sum = 0;
  for (int i = from; i < to; ++i) {
    int first_element = max(0, i - k + 1);
    int first_element_bucket = first_element / B;
    if (first_element_bucket != cached_bucket) {
      min2 = LLINF;

      int fully_included_bucket = first_element_bucket + 1;
      if (fully_included_bucket < my_node_id) {
        for (int j = fully_included_bucket; j < my_node_id; ++j) {
          min2 = min(min2, min_value_per_seg[j]);
        }
      }

      // prices.clear();
      Q.clear();

      if (first_element_bucket != my_node_id) {
        int last_element_of_first_bucket =
            min(first_element_bucket * B + B, n) - 1;
        for (int j = first_element; j <= last_element_of_first_bucket; ++j) {
          // prices.insert(GetGasPrice(j));
          Q.push(GetGasPrice(j));
        }
      }
      for (int j = max(from, i - k + 1); j <= i; ++j) {
        // prices.insert(GetGasPrice(j));
        Q.push(GetGasPrice(j));
      }
      cached_bucket = first_element_bucket;
    } else {
      // prices.insert(GetGasPrice(i));
      Q.push(GetGasPrice(i));

      int j = i - k;
      if (j >= 0) {
        // prices.erase(prices.find(GetGasPrice(j)));
        // assert(Q.top() == GetGasPrice(j));
        Q.pop();
      }
    }
    ll min1 = Q.min();  //*prices.begin();
    sum += min(min1, min2);
  }
  if (!is_master()) {
    PutLL(master_node(), sum);
    Send(master_node());
  } else {
    for (int nod = 1; nod < number_of_nodes; ++nod) {
      Receive(nod);
      sum += GetLL(nod);
    }
    cout << sum << "\n";
  }

  /*multiset<int> s;
  int n = GetNumKms(); int k = GetTankSize();
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    s.insert(GetGasPrice(i));
    int j = i - k;
    if (j >= 0) {
      s.erase(s.find(GetGasPrice(j)));
    }
    ans += *s.begin();
  }
  cout << ans << "\n";*/

  return 0;
}

int main2() {
  std::ios_base::sync_with_stdio(false);

  // int n = NumberOfFiles();
  // int k = MaxDistance();
  // int B = calc_single_processor_range_length(n);
  number_of_nodes = 1;
  if (useless_node()) {
    return 0;
  }

  multiset<int> s;
  int n = GetNumKms();
  int k = GetTankSize();
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    s.insert(GetGasPrice(i));
    int j = i - k;
    if (j >= 0) {
      s.erase(s.find(GetGasPrice(j)));
    }
    ans += *s.begin();
  }
  cout << ans << "\n";

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
