#include "winning_move-2.h"
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

struct Task {
  int begin;
  int end;
  void sent_to(int node) const {
    PutInt(node, begin);
    PutInt(node, end);
    Send(node);
  }

  static Task receive_from(int node) {
    Task m;
    Receive(node);
    m.begin = GetInt(node);
    m.end = GetInt(node);
    return m;
  }
};

struct Answer {
  vector<ll> data;

  void sent_to(int node) const {
    PutInt(node, (int)data.size());
    for (ll x : data) {
      PutLL(node, x);
    }
    Send(node);
  }

  static Answer receive_from(int node) {
    Answer m;
    Receive(node);
    m.data.resize(GetInt(node));
    for (ll &x : m.data) {
      x = GetLL(node);
    }
    return m;
  }
};

vector<ll> process(const vector<ll> &data) {
  size_t i = 0;
  vector<ll> out;
  out.reserve(data.size());
  while (i < data.size()) {
    size_t j = i;
    while (j < data.size() && data[j] == data[i]) {
      ++j;
    }
    if (j == i + 1) {
      out.push_back(data[i]);
    }
    i = j;
  }
  return out;
}

// int GetNumPlayers2() { return 10 * 1000; }
// int GetSubmission2(int i) { return i; }

int main() {
  std::ios_base::sync_with_stdio(false);

  // int B = calc_single_processor_range_length(n);

  if (useless_node()) {
    return 0;
  }
  int n = GetNumPlayers();
  if (is_master()) {
    Task t;
    t.begin = 0;
    t.end = n;
    t.sent_to(1);

    Answer ans = Answer::receive_from(1);
    auto data = ans.data;
    data = process(data);
    if (data.empty()) {
      cout << "0\n";
    } else {
      cout << data[0] << "\n";
    }

  } else {
    Task task = Task::receive_from(my_node_id / 2);
    vector<ll> data;
    if (my_node_id * 2 + 1 < number_of_nodes) {
      Task task1, task2;
      task1.begin = task.begin;
      task2.end = task.end;
      task1.end = task2.begin = (task.begin + task.end) / 2;
      task1.sent_to(my_node_id * 2);
      task2.sent_to(my_node_id * 2 + 1);

      Answer ans1 = Answer::receive_from(my_node_id * 2);
      Answer ans2 = Answer::receive_from(my_node_id * 2 + 1);
      data.resize(ans1.data.size() + ans2.data.size());
      merge(all(ans1.data), all(ans2.data), data.begin());
    } else {
      for (int i = task.begin; i < task.end; ++i) {
        data.push_back(GetSubmission((i + 12345678) % n));
      }
      sort(all(data));
    }
    data = process(data);
    const int limit = n / 2 + 10;
    if (data.size() > limit) {
      data.resize(limit);
    }
    Answer ans;
    ans.data = std::move(data);
    ans.sent_to(my_node_id / 2);
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
