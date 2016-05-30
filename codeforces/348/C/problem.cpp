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
typedef pair<long double, long double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const long double PI = 3.1415926535897932384626433832795;
const long double EPS = 1e-6;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

long double m_sqrt(long double x) {
  assert(x >= 0);
  long double lower = max<long double>(0.0, sqrtl(x) - 1);
  long double upper = sqrtl(x) + 1;
  for (int it = 0; it < 100; ++it) {
    auto m = (lower + upper) / 2;
    if (m * m > x) {
      upper = m;
    } else {
      lower = m;
    }
  }
  assert(fabs(lower * lower - x) < EPS);
  return 0.5 * (lower + upper);
}

pdd solve(long double a, long double b, long double c) {
  long double D = fabs(b * b - 4 * a * c);
  long double p1 = (-b + m_sqrt(D)) / 2 / a;
  long double p2 = (-b - m_sqrt(D)) / 2 / a;
  return pdd(p2, p1);
}

int main() {
  int n;
  scanf("%d", &n);
  vector<long double> a(n);
  vector<long double> b(n);
  vector<long double> m(n);
  vector<long double> M(n);
  long double B, C, A;
  B = C = A = 0;
  for (int i = 0; i < n; ++i) {
    double x;
    scanf("%lf", &x);
    M[i] = x;
  }
  for (int i = 0; i < n; ++i) {
    double x;
    scanf("%lf", &x);
    m[i] = x;
  }
  for (int i = 0; i < n; ++i) {
    C = m[i] + M[i];

    auto s = solve(-1.0, C - B + A, C * B - M[i]);
    debug(C);
    debug(s);

    long double p = s.first;
    if (p < 0 || p > C || p + B > 1.0 || A + (C - p) > 1.0) {
      p = s.second;
    }

    b[i] = p;
    a[i] = C - p;
    B += b[i];
    A += a[i];
    debug(A);
    debug(B);
  }
  assert(fabs(1.0 - A) < EPS);
  assert(fabs(1.0 - B) < EPS);
  debug(a);
  debug(b);
  debug(accumulate(all(a), 0.0));
  debug(accumulate(all(b), 0.0));
  for (int i = 0; i < n; ++i) {
    printf("%0.9lf ", double(a[i]));
  }
  printf("\n");
  for (int i = 0; i < n; ++i) {
    printf("%0.9lf ", double(b[i]));
  }
  printf("\n");
  return 0;
}
