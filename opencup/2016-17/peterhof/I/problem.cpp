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

vector<vector<int>> out;

struct PerfectMatching {
  explicit PerfectMatching(int n)
      : left_counterpart(n, -1), right_counterpart(n, -1) {}

  void add_edge(int l, int r) {
    left_counterpart[r] = l;
    right_counterpart[l] = r;
  }

  void check_dbg() const {
#ifdef LOCAL_RUN
    for (size_t i = 0; i < left_counterpart.size(); ++i) {
      assert(right_counterpart[left_counterpart[i]] == i);
    }
#else
#endif
  }
  void print() const { out.push_back(right_counterpart); }
  void print_debug() const {
#ifdef LOCAL_RUN
    cerr << "----\n";
    for (size_t i = 0; i < right_counterpart.size(); ++i) {
      cerr << i << " - " << right_counterpart[i] << "\n";
    }
    cerr << "----\n";
#else
#endif
  }

  vi left_counterpart;
  vi right_counterpart;
};

bool kuhn(int l, vector<bool> &used, PerfectMatching &pm,
          const vii &from_left_to_right) {
  if (used[l]) {
    return false;
  }
  used[l] = true;
  for (int r : from_left_to_right[l]) {
    if (pm.left_counterpart[r] == -1 ||
        kuhn(pm.left_counterpart[r], used, pm, from_left_to_right)) {
      pm.add_edge(l, r);
      return true;
    }
  }
  return false;
}

// z is right
void find_reachable(int z, const vii &from_right_to_left,
                    const PerfectMatching &matching, vi &predecessor_of_left,
                    const vector<bool> &is_right_fixed) {
  if (is_right_fixed[z]) {
    return;
  }
  for (int left : from_right_to_left[z]) {
    if (predecessor_of_left[left] == -1) {
      predecessor_of_left[left] = z;
      find_reachable(matching.right_counterpart[left], from_right_to_left,
                     matching, predecessor_of_left, is_right_fixed);
    }
  }
}

void rec(int x, vector<bool> &is_right_fixed, const vii &from_left_to_right,
         const vii &from_right_to_left, const PerfectMatching &matching) {
  debug(x);
  debug(is_right_fixed);
  int n = (int)is_right_fixed.size();
  if (x == n) {
    matching.print();
    return;
  }
  matching.print_debug();
  int y = matching.right_counterpart[x];
  assert(!is_right_fixed[y]);
  vi predecessor_of_left(n, -1);

  /*
   * for (int i = 0; i < n; ++i) {
   * if (is_right_fixed[i]) {
   *predecessor_of_left[mathcing.left_cou[i]] = -2;
   * }
   * }
   */

  find_reachable(y, from_right_to_left, matching, predecessor_of_left,
                 is_right_fixed);
  for (int right : from_left_to_right[x]) {
    if (!is_right_fixed[right]) {
      int left = matching.left_counterpart[right];
      if (predecessor_of_left[left] >= 0) {
        PerfectMatching new_matching(matching);
        while (left != x) {
          new_matching.add_edge(left, predecessor_of_left[left]);
          left = matching.left_counterpart[predecessor_of_left[left]];
        }
        new_matching.add_edge(x, right);
        new_matching.check_dbg();
        is_right_fixed[right] = 1;
        rec(x + 1, is_right_fixed, from_left_to_right, from_right_to_left,
            new_matching);
        is_right_fixed[right] = 0;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  vii from_left_to_right(n);
  vii from_right_to_left(n);
  {
    int m;
    cin >> m;
    vector<vector<bool>> am(n, vector<bool>(n, true));
    for (int i = 0; i < m; ++i) {
      int a, b;
      cin >> a >> b;
      --a;
      --b;
      am[a][b] = false;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (am[i][j]) {
          from_left_to_right[i].push_back(j);
          from_right_to_left[j].push_back(i);
        }
      }
    }
  }
  PerfectMatching matching(n);
  {
    bool has = true;
    for (int i = 0; i < n; ++i) {
      vector<bool> used(n);
      has = has && kuhn(i, used, matching, from_left_to_right);
    }
    if (!has) {
      cout << "0\n";
      return 0;
    }
  }
  debug(matching.left_counterpart);
  debug(matching.right_counterpart);

  matching.check_dbg();

  vector<bool> is_right_fixed(n);
  rec(0, is_right_fixed, from_left_to_right, from_right_to_left, matching);
  cout << out.size() << "\n";
  for (const auto &x : out) {
    for (int y : x) {
      cout << y + 1 << " ";
    }
    cout << "\n";
  }
  return 0;
}
