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

int main() {
  // std::ios_base::sync_with_stdio(false);

  int n;
  scanf("%d", &n);
  pair<int, vector<int>> men_odd;  // start seq
  pair<int, vector<int>> men_even;
  men_odd.first = men_even.first = 0;
  for (int i = 1; i <= n; ++i) {
    if (i & 1) {
      men_odd.second.push_back(i);
    } else {
      men_even.second.push_back(i);
    }
  }
  int q;
  scanf("%d", &q);
  while (q-- > 0) {
    int t;
    scanf("%d", &t);
    if (t == 1) {
      int x;
      scanf("%d", &x);
      if (x < 0) {
        x += n;
      }

      if (x & 1) {
        men_even.swap(men_odd);
      }
      int o = (x + 1) / 2;
      int e = (x) / 2;
      men_even.first = (men_even.first + e) % (n / 2);
      men_odd.first = (men_odd.first + o) % (n / 2);
    } else {
      men_even.swap(men_odd);
    }
  }
  vi boys(n);
  for (int i = 0; i < n; ++i) {
    const auto &c = (i % 2 == 0) ? men_odd : men_even;
    int j = (i / 2);
    int k = (n + j - c.first) % (n / 2);
    boys[i] = (c.second[k]);
  }

  /*debug(boys);
  vi girls(n, -1);
  for (int i = 0; i < n; ++i) {
    girls[boys[i] - 1] = i;
  }*/
  for (int b : boys) {
    printf("%d ", b);
  }
  printf("\n");

  return 0;
}
