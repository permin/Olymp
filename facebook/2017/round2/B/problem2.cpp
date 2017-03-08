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

void gen(vi &x, ll a, ll b, ll c) {
  for (size_t i = 1; i < x.size(); ++i) {
    x[i] = int((a * x[i - 1] + b) % c) + 1;
  }
}

void SolveTest() {
  int n;
  cin >> n;
  vi x(n);
  cin >> x[0];
  int ax, bx, cx;
  cin >> ax >> bx >> cx;
  vi h(n);
  int ah, bh, ch;
  cin >> h[0];
  cin >> ah >> bh >> ch;
  gen(x, ax, bx, cx);
  gen(h, ah, bh, ch);
  debug(x);
  debug(h);
  for (int &a : x) {
    a *= 2;
  }
  for (int &a : h) {
    a *= 2;
  }
  int first = -2 * ch - 100;
  int last = 2 * (cx + ch) + 100;
  vi height(last - first + 1);
  vi sticks(last - first + 1);
  for (int i = 0; i < n; ++i) {
    sticks[x[i]] = max(sticks[x[i] - first], h[i]);
  }

  {
    int curHeight = 0;
    for (int k = first; k <= last; ++k) {
      curHeight -= 1;
      curHeight = max(curHeight, 0);
      curHeight = max(curHeight, sticks[k - first]);
      height[k - first] = curHeight;
    }
  }
  {
    int curHeight = 0;
    for (int k = last; k >= first; --k) {
      curHeight -= 1;
      curHeight = max(curHeight, 0);
      curHeight = max(curHeight, sticks[k - first]);
      height[k - first] = curHeight;
    }
  }
  double area = 0;
  for (int k = first; k < last; ++k) {
    area += 0.5 * (height[k] + height[k + 1]);
  }
  printf("%0.18lf\n", area / 4);
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  int tests = 0;
  cin >> tests;
  for (int testIndex = 0; testIndex < tests; ++testIndex) {
    cout << "Case #" << testIndex + 1 << ": ";
    // cerr << "Case #" << testIndex + 1 << ": ...\n";
    SolveTest();
  }
  return 0;
}
