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

bool ok(const string &str, int r, int p, int s) {
  return std::count(all(str), 'R') == r && std::count(all(str), 'S') == s &&
         std::count(all(str), 'P') == p;
}

string gen(char ch, int len) {
  if (len == 1) {
    return string(1, ch);
  } else {
    if (ch == 'P') {
      return gen('P', len / 2) + gen('R', len / 2);
    } else if (ch == 'R') {
      return gen('R', len / 2) + gen('S', len / 2);
    } else if (ch == 'S') {
      return gen('P', len / 2) + gen('S', len / 2);
    } else {
      assert(0);
    }
  }
  return {};
}

string norm(string str) {
  int n = (int)str.size();
  for (int step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += step * 2) {
      if (str.substr(i, step) > str.substr(i + step, step)) {
        for (int k = 0; k < step; ++k) {
          swap(str[i + k], str[i + k + step]);
        }
      }
    }
  }
  return str;
}

void solve_test() {
  string res;
  int n;
  cin >> n;
  n = 1 << n;
  int r, p, s;
  cin >> r >> p >> s;
  assert(n == r + p + s);

  vector<string> c;
  c.push_back(norm(gen('P', n)));
  c.push_back(norm(gen('R', n)));
  c.push_back(norm(gen('S', n)));
  for (int i = 0; i < 3; ++i) {
    if (ok(c[i], r, p, s)) {
      if (res == "" || res > c[i]) {
        res = c[i];
      }
    }
  }
  if (res.empty()) {
    res = "IMPOSSIBLE";
  }

  cout << res << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; ++t) {
    cout << "Case #" << t + 1 << ": ";
    solve_test();
  }
  return 0;
}
