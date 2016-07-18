#include "sandwich.h"
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

template <class It>
class IteratorRange {
 public:
  IteratorRange(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

 private:
  It begin_;
  It end_;
};

template <class It>
IteratorRange<It> make_iterator_range(It begin, It end) {
  return IteratorRange<It>(begin, end);
}

namespace communication {

namespace impl {}
const size_t kMessageSize = 8 * (1 << 20);

template <class T>
void put_to_node(int node, T value);

template <class T>
struct TransitionPreparer {
  static T get(int node);
  static void put(int node, T value);
};
template <>
struct TransitionPreparer<int> {
  static int get(int node) { return GetInt(node); }
  static void put(int node, int value) { PutInt(node, value); }
};
template <>
struct TransitionPreparer<ll> {
  static int get(int node) { return GetLL(node); }
  static void put(int node, ll value) { PutLL(node, value); }
};
template <>
struct TransitionPreparer<char> {
  static char get(int node) { return GetChar(node); }
  static void put(int node, char value) { PutChar(node, value); }
};

template <>
struct TransitionPreparer<std::tuple<>> {
  static std::tuple<> get(int node) { return std::tuple<>(); }
  static void put(int node, std::tuple<>) {}
};

template <class T, class... Args>
struct TransitionPreparer<tuple<T, Args...>> {
  static tuple<T, Args...> get(int node) {
    T first = TransitionPreparer<T>::get(node);
    return std::tuple_cat(std::make_tuple(first),
                          TransitionPreparer<std::tuple<Args...>>::get(node));
  }
  static tuple<T, Args...> put(int node, tuple<T, Args...> value) {
    TransitionPreparer<T>::put(node, std::get<0>(value));
    // TODO implement put for tail
    //
    // TransitionPreparer<tuple<Args...>>::put(node,
    //                                        make_tuple(std::get<1,
    //                                        2>(value)));
  }
};

// const static int kElementsPerMessage = (kMessageSize - sizeof(int)) /
// sizeof(T);

template <class It>
struct TransitionPreparer<IteratorRange<It>> {
  static typename std::enable_if<
      std::is_pod<typename std::iterator_traits<It>::value_type>::value,
      std::vector<std::iterator_traits<It>::value_type>>::value
  get(int node) {}
};

template <class T>
T get_from_node(int node);

/*template <class T, class... Args>
std::tuple<T, Args...> get_from_node<std::tuple<T, Args...>>(int node);
*/
template <>
ll get_from_node<ll>(int node) {
  return GetLL(node);
}

template <>
int get_from_node<int>(int node) {
  return GetInt(node);
}

template <>
char get_from_node<char>(int node) {
  return GetChar(node);
}
}

class DistributionByIndex {
 public:
  DistributionByIndex(long long sequence_length, int buckets)
      : sequence_length_(sequence_length), buckets_(buckets) {
    assert(sequence_length_ >= buckets_);
  }

  ll begin_for_node(int i) const {
    assert(i <= buckets_);
    return min((sequence_length_ / buckets_) * (i) +
                   min<ll>(i, sequence_length_ % buckets_),
               sequence_length_);
  }

  int end_for_node(int i) const { return begin_for_node(i + 1); }

 private:
  long long sequence_length_;
  int buckets_;
};

template <class Message>
void broadcast(const Message &m) {
  for (int node = 0; node < number_of_nodes; ++node) {
    if (node != my_node_id) {
      send(m, node);
    }
  }
}

template <class Message>
Message sync(const Message &m, int root) {
  if (root == my_node_id) {
    broadcast(m);
    return m;
  } else {
    return receive<Message>(root);
  }
}

:wqaint main() {
  std::ios_base::sync_with_stdio(false);

  int n = GetN();
  // int k = MaxDistance();
  // int B = calc_single_processor_range_length(n);
  number_of_nodes = min(number_of_nodes, n);

  if (useless_node()) {
    return 0;
  }

  DistributionByIndex elements_distribution(n, number_of_nodes);
  debug(n);
  debug(my_node_id);
  debug(elements_distribution.begin_for_node(my_node_id));
  debug(elements_distribution.end_for_node(my_node_id));

  typedef std::tuple<int, char, ll> Message;
  communication::TransitionPreparer<Message>::put(0, Message(1, 2, 3));
  communication::TransitionPreparer<Message>::get(0);

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
