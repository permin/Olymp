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

template <class T> class IsIterable__ {
  static void f(...);
  template <class U> static typename U::const_iterator f(const U &);

public:
  const static bool value =
      !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S>
ostream &operator<<(ostream &o, const pair<F, S> &p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C> void O__(ostream &o, const C &c) {
  bool f = 1;
  for (const auto &x : c) {
    if (!f)
      o << ", ";
    if (IsIterable__<decltype(x)>::value)
      o << "\n";
    f = 0;
    o << x;
  }
}

template <class T> ostream &operator<<(ostream &o, const vector<T> &v) {
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

template <class T> ostream &operator<<(ostream &o, const set<T> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

typedef unsigned int Int;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<Int> vi;
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

Int make(char a, char b, char c, char d) {
  return (Int(d) << 24) | (Int(c) << 16) | (Int(b) << 8) | Int(a);
}

string Str(Int i) {
  stringstream o;
  o << i;
  return o.str();
}

void go(Int n, string &out) {
  if (n == 1)
    return;
  for (Int i = 2; i <= 10; ++i) {
    while (n % i == 0) {
      out += " * " + Str(i);
      n /= i;
    }
  }
  if (n == 1)
    return;
  for (int i = 10; i <= n; ++i) {
    while (n % i == 0) {
      out += " * (1";
      go(i - 1, out);
      out += " + 1)";
      n /= i;
    }
  }
}

vi factor(Int n) {
  vi r;
  for (Int i = 2; i <= n; ++i) {
    while (n % i == 0) {
      n /= i;
      r.emplace_back(i);
    }
  }
  return r;
}

int main() {
  srand(23);
  Int b[] = {make('H', 'a', 'p', 'p'), make('y', ' ', 'b', 'i'),
             make('r', 't', 'h', 'd'), make('a', 'y', '!', 0)};

  Int c[] = {1 * 2 * 2 * 2 * 3 *
                 (1 * 2 * (1 * 2 * 7 * (1 * 2 * 2 * 2 * 2 + 1) + 1) + 1) *
                 (1 * 2 * 2 * (1 * 2 * 3 * 3 * (1 * 2 * 3 * 7 + 1) *
                                   (1 * 2 * 2 * (1 * 2 * 2 * 3 + 1) + 1) +
                               1) +
                  1),
             1 * (1 * 2 * 3 * 3 + 1) * (1 * 2 * 5 * 7 + 1) *
                 (1 * 2 * 2 * 3 * (1 * 2 * 5 + 1) *
                      (1 * 2 * 2 * 2 * (1 * 2 * 2 * 2 * 2 + 1) *
                           (1 * 2 * 2 * 2 * 3 * 3 + 1) +
                       1) +
                  1),
             1 * 2 * (1 * 2 * 2 * 3 * 3 + 1) *
                 (1 * 2 * 3 * 5 * (1 * 2 * 5 * (1 * 2 * 2 * 3 + 1) + 1) + 1) *
                 (1 * 2 * 3 * 5 * (1 * 2 * 2 * 2 * 2 * 2 * 2 * 3 + 1) + 1),
             1 * (1 * 2 * 2 * 2 * (1 * 2 * 5 + 1) + 1) *
                 (1 * 2 * 2 * 3 * (1 * 2 * 2 * 3 + 1) + 1) *
                 (1 * 2 * 2 * 3 * (1 * 2 * 2 * 3 + 1) + 1)};
  cerr << "Int c[] = {";
  for (int i = 0; i < 4; ++i) {
    string out = "1 ";
    go(b[i], out);
    cerr << out << ", ";
  }
  printf("%s\n", (char *)&(c));
  return 0;
}
