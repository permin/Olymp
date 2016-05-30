#include "winning_move.h"
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
typedef unsigned long long ull;
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

const int LEN = 16;
const int BASE = 1 << 16;

template <class F>
vector<ull> stable_sort(const vector<ull> &data, F extract_key) {
  std::vector<ll> num(BASE);
  for (ll x : data) {
    ++num[extract_key(x)];
  }
  vector<ll> pos(BASE);
  ull sum = 0;
  for (int i = 0; i < BASE; ++i) {
    pos[i] = sum;
    sum += num[i];
  }
  vector<ull> res(data.size(), -1);
  for (ull x : data) {
    int key = extract_key(x);
    res[pos[key]] = x;
    ++pos[key];
  }
  return res;
}

vector<ull> fast_sort(vector<ull> data) {
  for (int i = 0; i < 64 / LEN; ++i) {
    data = stable_sort(data, [&](ull x) -> int {
      return ((x >> (LEN * i)) & (ull(BASE - 1)));
    });
  }
  return data;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n = GetNumPlayers();
  /*int sq = 1;
  while ((sq + 1) * (sq + 1) <= number_of_nodes && (sq + 1) * (sq + 1) <= n) {
    ++sq;
  }
  number_of_nodes = sq * sq;
  int B = (n + sq - 1) / sq;
  assert(number_of_nodes == sq * sq);
*/
  number_of_nodes = 1;
  if (useless_node()) {
    return 0;
  }
  vector<ull> data;
  for (int i = 0; i < 35 * 1000 * 1000; ++i) {
    ull a = rand() % BASE;
    ull b = rand() % BASE;
    ull c = rand() % BASE;
    ull d = rand() % BASE;
    data.push_back(a + (b << 16) + (c << 32) + (d << 48));
  }
  data = fast_sort(data);
  assert(is_sorted(all(data)));

  // int a = my_node_id / sq;
  // int b = my_node_id % sq;

  // int from = a * B;
  // int to = min(n, from + B);
  /*vector<ull> data;
  for (int i = 0; i < n; ++i) {
    data.push_back(GetSubmission(i));
  }

  data = fast_sort(data);

  ull ans = 0;
  size_t i = 0;
  while (i < data.size()) {
    size_t j = i + 1;
    while (j < data.size() && data[j] == data[i]) {
      ++j;
    }
    if (j == i + 1) {
      ans = data[i];
      break;
    } else {
      i = j;
    }
  }

  if (!is_master()) {
    PutLL(master_node(), ans);
    Send(master_node());
  } else {
    for (int node = 1; node < number_of_nodes; ++node) {
      Receive(node);
      ull cand = GetLL(node);
      if (cand == 0) continue;
      if (ans == 0) {
        ans = cand;
      } else {
        ans = min(ans, cand);
      }
    }
    cout << ans << "\n";
  }*/

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
