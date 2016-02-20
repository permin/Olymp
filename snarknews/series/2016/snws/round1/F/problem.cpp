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

bool is_possible_to_finish(int last, const vi &stat) {
  int rem = 0;
  for (int i : stat) {
    rem += i;
  }
  int most_frequest_char = 0;
  for (int i = 0; i < 26; ++i) {
    if (stat[most_frequest_char] < stat[i]) {
      most_frequest_char = i;
    }
  }
  if (last == most_frequest_char && 2 * stat[most_frequest_char] > rem) {
    return false;
  }
  if (last != most_frequest_char && stat[most_frequest_char] > (rem + 1) / 2) {
    return false;
  }
  return true;
}

string solve(const string &s) {
  vi stat(26);
  for (char ch : s) {
    stat[ch - 'a'] += 1;
  }
  string res(s.size(), '?');
  for (int i = 0; i < (int)s.size(); ++i) {
    bool found = false;
    for (int c = 0; c < 26; ++c) {
      if (stat[c] > 0 && (i == 0 || char(c + 'a') != res[i - 1])) {
        stat[c] -= 1;
        if (is_possible_to_finish(c, stat)) {
          res[i] = char('a' + c);
          found = true;
          break;
        }
        stat[c] += 1;
      }
    }
    if (!found) {
      return "IMPOSSIBLE";
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  while (n-- > 0) {
    string s;
    cin >> s;
    cout << solve(s) << "\n";
  }
  return 0;
}
