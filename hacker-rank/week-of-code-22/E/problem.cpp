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

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": " << (x) << "\n";
#else
#define debug(x) ;
#endif

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

struct Block {
  Block() { xor_pref.push_back(0); }

  void do_assign(int x, int t) {
    assign = x;
    assign_at = t;
    xor_req_time.clear();
    xor_pref.resize(1);
  }
  void do_xor(int x, int t) {
    xor_req_time.push_back(t);
    xor_pref.push_back(xor_pref.back() ^ x);
  }
  int get_xor_after(int t) {
    int i =
        (int)(std::lower_bound(all(xor_req_time), t) - xor_req_time.begin());
    return xor_pref.back() ^ xor_pref[i];
  }

  int assign = 0;
  int assign_at = 0;
  std::vector<int> xor_pref;
  std::vector<int> xor_req_time;
};

template <class F>
void for_all_subsets(int mask, F f) {
  for (int x = mask;; x = (x - 1) & mask) {
    f(x);
    if (x == 0) break;
  }
}
template <class F>
void for_all_super_sets(int mask, int super, F f) {
  int add = super ^ mask;
  for (int x = add;; x = (x - 1) & add) {
    f(x | mask);
    if (x == 0) break;
  }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);

  int part1 = n / 2;
  int part2 = n - part1;

  vector<vector<Block>> blocks(1 << part1, vector<Block>(1 << part2));

  auto get_first_part = [part2](int mask) { return mask >> part2; };
  auto get_second_part = [part2](int mask) {
    return mask & ((1 << part2) - 1);
  };

  int timer = 0;
  while (q-- > 0) {
    ++timer;
    int t;
    int s;
    char buf[123];
    scanf("%d", &t);
    if (t == 3) {
      scanf("%s", buf);
      s = (int)strtol(buf, NULL, 2);

      int first = get_first_part(s);
      int second = get_second_part(s);
      int assign_time = -1;
      int val = 0;
      int super_second = (1 << part2) - 1;
      for_all_super_sets(second, super_second, [&](int mask) {
        if (blocks[first][mask].assign_at > assign_time) {
          assign_time = blocks[first][mask].assign_at;
          val = blocks[first][mask].assign;
        }
      });
      for_all_super_sets(second, super_second, [&](int mask) {
        val ^= blocks[first][mask].get_xor_after(assign_time);
      });
      printf("%d\n", val);

    } else {
      int y;
      scanf("%d", &y);
      scanf("%s", buf);
      s = (int)strtol(buf, NULL, 2);

      int first = get_first_part(s);
      int second = get_second_part(s);
      if (t == 1) {
        for_all_subsets(first,
                        [&](int x) { blocks[x][second].do_assign(y, timer); });
      } else {
        for_all_subsets(first,
                        [&](int x) { blocks[x][second].do_xor(y, timer); });
      }
    }
  }
  return 0;
}
