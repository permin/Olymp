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

const int mod = 1000 * 1000 * 1000 + 7;
int add(int x, int y) { return (x + y) % mod; }
int mul(int x, int y) { return int((1LL * x * y) % mod); }
const int maxN = 50 * 1000 * 1000 + 10;

int p6[maxN];
int psum[maxN];

string add(string a, string b, int *was) {
  if (a.size() > b.size()) {
    return add(b, a, was);
  }
  if (a.size() < b.size()) {
    a = string(b.size() - a.size(), '0') + a;
  }
  string c(a.size() + 1, '0');
  int car = 0;
  for (int i = int(a.size()) - 1; i >= 0; --i) {
    int val = (int(a[i] - '0') + int(b[i] - '0') + car);
    car = val > 9;
    c[i + 1] = char('0' + (val % 10));
    if (car) {
      *was = 1;
    }
  }
  if (car) {
    c[0] = '1';
  }
  if (car) {
    *was = 1;
  }
  return c;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  for (int i = 0; i < maxN; ++i) {
    p6[i] = i == 0 ? 1 : mul(5, p6[i - 1]);
    psum[i] = i == 0 ? 0 : add(psum[i - 1], p6[i - 1]);
  }
  string s1;
  int n;
  cin >> s1 >> n;
  string s;
  for (int i = 0; i < n; ++i) {
    s += s1;
  }

  int total = 0;
  for (char d : s) {
    total = add(mul(total, 10), d - '0');
  }
  total = add(total, 1);

  bool viol = 0;
  int res = 0;
  for (int match = 0; match < (int)s.size(); ++match) {
    for (int x = 0; x <= 4; ++x) {
      if (x >= (s[match] - '0')) {
        continue;
      }
      if (x <= 4) {
        res = add(res, 1);
      }
      int len = int(s.size()) - match - 1;
      res = add(res, mul(5, psum[len]));
    }
    debug(match);
    debug(res);
    viol = viol || (s[match] - '0' >= 5);
    if (viol) {
      bool all9 = 1;
      for (int i = match; i < (int)s.size(); ++i) {
        all9 = all9 && s[i] == '9';
      }
      if (all9) res = add(res, 1);
      break;
    }
  }
  debug(res);
  if (!viol) {
    res = add(res, 1);
  }
  int ans = add(mod - res, total);
  debug(res);
  debug(total);
  cout << ans << "\n";

  {
    stringstream o(s);
    int x;
    o >> x;
    int cor = 0;
    for (int i = 1; i <= x; ++i) {
      stringstream o2;
      o2 << i;
      string s2;
      o2 >> s2;
      int f = 0;
      string s3 = add(s2, "1", &f);
      f = 0;
      auto s4 = add(s2, s3, &f);
      if (f) {
        ++cor;
      } else {
        debug(i);
      }
    }
    debug(cor);
    assert(cor == ans);
  }
  return 0;
}
