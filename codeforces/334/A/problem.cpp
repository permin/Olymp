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
#include <initializer_list>
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

int count(string s) {
  char ch = '?';
  int res = 0;
  for (char c : s) {
    if (ch != c) {
      ch = c;
      ++res;
    }
  }
  return res;
}

int solve(string s) {
  int res = count(s);
  return res + 2;
  bool f3 = 0;
  for (auto su : {"11", "00"}) {
    size_t x = s.find(su);
    if (x != string::npos) {
      if (s.find(su, x + 1) != string::npos) {
        f3 = 1;
        break;
      }
    }
  }
  f3 = f3 || s.find("0011", 0) != string::npos;
  f3 = f3 || s.find("1100", 0) != string::npos;
  f3 = f3 ||
       (s.find("11", 0) != string::npos && s.find("00", 0) != string::npos);
  if (f3) {
    res += 2;
  } else {
    bool f2 = 0;
    for (auto su : {"11", "00"}) {
      size_t x = s.find(su);
      if (x != string::npos) {
        f2 = 1;
        break;
      }
    }
    if (f2)
      res += 1;
  }
  return res;
}

int stSolve(const string s) {
  int len;
  {
    string s2 = s;
    len = int(unique(all(s2)) - s2.begin());
  }
  for (size_t i = 0; i < s.size(); ++i) {
    for (size_t j = i; j < s.size(); ++j) {
      string s2 = s;
      for (size_t k = i; k <= j; ++k) {
        s2[k] ^= '0';
        s2[k] ^= '1';
      }
      len = max(len, int(unique(all(s2)) - s2.begin()));
    }
  }
  return len;
}

void g() {
  for (;;) {
    int l = rand() % 20;
    ++l;
    string s(l, '3');
    for (char &c : s) {
      if (rand() & 1)
        c = '0';
      else
        c = '1';
    }
    debug(s);
    debug(solve(s));
    debug(stSolve(s));
    assert(solve(s) == stSolve(s));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  string s;
  cin >> s;
  cout << solve(s) << "\n";
  // cout << stSolve(s) << "\n";

  return 0;
}
