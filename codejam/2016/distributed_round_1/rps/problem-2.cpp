#include "rps-2.h"
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

const pair<char, int> &winner(const pair<char, int> &a,
                              const pair<char, int> &b) {
  if (a.first == b.first) {
    return a;
  }
  char ch_a = a.first;
  char ch_b = b.first;
  if (ch_a == 'R' && ch_b == 'S') {
    return a;
  }
  if (ch_a == 'S' && ch_b == 'P') {
    return a;
  }
  if (ch_a == 'P' && ch_b == 'R') {
    return a;
  }
  return b;
}

vector<pair<char, int>> process(const vector<pair<char, int>> &input) {
  vector<pair<char, int>> output;
  for (int i = 0; i < input.size(); i += 2) {
    output.emplace_back(std::move(winner(input[i], input[i + 1])));
  }
  return output;
}

pair<char, int> get_winner(vector<pair<char, int>> input) {
  while (input.size() > 1) {
    input = process(input);
  }
  return input.front();
}

int main() {
  std::ios_base::sync_with_stdio(false);

  // int n = NumberOfFiles();
  // int k = MaxDistance();
  // int B = calc_single_processor_range_length(n);

  int n = GetN();
  int slaves = 1;
  while (slaves * 2 + 1 < number_of_nodes && 2 * slaves <= (1 << n)) {
    slaves *= 2;
  }
  number_of_nodes = slaves + 1;

  if (useless_node()) {
    return 0;
  }
  int B = (1 << n) / slaves;

  if (!is_master()) {
    int i = my_node_id - 1;
    int from = B * i;
    int to = from + B;
    vector<pair<char, int>> players;
    for (int i = from; i < to; ++i) {
      players.emplace_back(GetFavoriteMove(i), i);
    }
    auto s = get_winner(players);
    PutChar(master_node(), s.first);
    PutInt(master_node(), s.second);
    Send(master_node());
  } else {
    vector<pair<char, int>> players;
    for (int node = 1; node < number_of_nodes; ++node) {
      pair<char, int> a;
      Receive(node);
      a.first = GetChar(node);
      a.second = GetInt(node);
      players.emplace_back(std::move(a));
    }
    cout << get_winner(players).second << "\n";
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
