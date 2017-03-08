#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
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

typedef long long ll;

const int MAX = 16;

struct Complex {
  typedef double D;
  inline D imag() const { return i; }
  inline D real() const { return r; }
  D i, r;
  Complex() : i(0), r(0) {}
  Complex(D x) : i(0), r(x) {}
  Complex(D r, D i) : i(i), r(r) {}
  inline Complex &operator+=(const Complex &o) {
    r += o.r;
    i += o.i;
    return *this;
  }
  inline Complex &operator-=(const Complex &o) {
    r -= o.r;
    i -= o.i;
    return *this;
  }
  inline Complex &operator*=(D o) {
    r *= o;
    i *= o;
    return *this;
  }
  inline Complex &operator/=(D o) {
    r /= o;
    i /= o;
    return *this;
  }
  inline Complex &operator*=(const Complex &o) {
    D a = r * o.r - i * o.i;
    D b = r * o.i + i * o.r;
    r = a;
    i = b;
    return *this;
  }
  inline Complex &operator/=(const Complex &o) {
    D a = r * o.r + i * o.i;
    D b = i * o.r - r * o.i;
    D c = o.r * o.r + o.i * o.i;
    r = a / c;
    i = b / c;
    return *this;
  }
};

inline Complex operator*(Complex a, const Complex &b) { return a *= b; }
inline Complex operator/(Complex a, const Complex &b) { return a /= b; }
inline Complex operator+(Complex a, const Complex &b) { return a += b; }
inline Complex operator-(Complex a, const Complex &b) { return a -= b; }
inline Complex operator*(Complex a, Complex::D b) { return a *= b; }
inline Complex operator/(Complex a, Complex::D b) { return a /= b; }

// typedef complex<double> base;
typedef Complex base;

namespace FFT {
int b[1 << MAX];
double c[1 << MAX];
double s[1 << MAX];
void FFT(int n, base *a, bool inv = false) {
  static int x = -1;
  if (x != n) {
    for (int i = 0; i < 25; ++i) {
      c[i] = cos(2.0 * PI / (1 << i));
      s[i] = sin(2.0 * PI / (1 << i));
    }
    for (int i = 1, j = 0; i < n; ++i) {
      int bit = n >> 1;
      for (; j >= bit; bit >>= 1) j -= bit;
      j += bit;
      b[i] = j;
    }
    x = n;
  }
  for (int i = 0; i < n; ++i) {
    if (b[i] < i) swap(a[i], a[b[i]]);
  }
  int p = 0;
  for (int len = 2; len <= n; len <<= 1) {
    ++p;
    base w1(c[p], inv ? -s[p] : s[p]);
    for (int i = 0; i < n; i += len) {
      base w(1);
      for (int j = 0; j < len / 2; ++j) {
        base u = a[i + j];
        base v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= w1;
      }
    }
  }
  if (inv)
    for (int i = 0; i < n; ++i) a[i] /= n;
}
}  // FFT

const int maxN = 200;
double subtrees[maxN];
typedef vector<base> Poly;
Poly ans[maxN];
int w[maxN];
int subtree_sum_costs[maxN];

void dfs(int v, const vii &al, int p = -1) {
  for (int v2 : al[v]) {
    if (v2 != p) {
      dfs(v2, al, v);
    }
  }
  subtree_sum_costs[v] = 0;
  int outdeg = 0;
  int child = -1;
  subtrees[v] = 1.0;
  for (int v2 : al[v]) {
    if (v2 != p) {
      child = v2;
      ++outdeg;
      subtrees[v] *= subtrees[v2] + 1;
      subtree_sum_costs[v] += subtree_sum_costs[v2];
    }
  }
  if (outdeg == 1) {
    subtree_sum_costs[v] += w[v];
    ans[v].clear();
    ans[v].resize(1 + subtree_sum_costs[v]);

    for (int i = 0; i < w[v]; ++i) {
      ans[v][i] = 0.0;
    }
    for (int i = w[v]; i < (int)ans[v].size(); ++i) {
      ans[v][i] =
          (subtrees[child] * ans[child][i - w[v]] + (i == w[v] ? 1.0 : 0.0)) /
          (subtrees[child] + 1);
    }

    return;
  }
  int n = 1;
  while (n <= subtree_sum_costs[v]) {
    n *= 2;
  }

  bool mul = false;
  Poly transformed_poly(n);
  for (int v2 : al[v]) {
    if (v2 != p) {
      Poly p = ans[v2];
      if ((int)p.size() < n) {
        p.resize(n);
      }
      assert((int)p.size() == n);
      for (auto &x : p) {
        x *= subtrees[v2];
      }
      p[0] += 1.0;
      for (auto &x : p) {
        x /= subtrees[v2] + 1;
      }
      FFT::FFT(n, p.data());
      if (!mul) {
        transformed_poly = p;
        mul = true;
      } else {
        for (int i = 0; i < n; ++i) {
          transformed_poly[i] *= p[i];
        }
      }
    }
  }
  if (mul) {
    FFT::FFT(n, transformed_poly.data(), true);
  } else {
    transformed_poly[0] = 1.0;
  }
  subtree_sum_costs[v] += w[v];
  ans[v].clear();
  ans[v].resize(1 + subtree_sum_costs[v]);

  for (int i = 0; i < w[v]; ++i) {
    ans[v][i] = 0.0;
  }
  for (int i = w[v]; i < (int)ans[v].size(); ++i) {
    ans[v][i] = transformed_poly[i - w[v]];
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  /*int n = 1 << 16;
  base *a = new base[n];
  vector<base> b;
  for (int i = 0; i < n; ++i) {
    a[i] = i % 1000;
    b.push_back(a[i]);
  }
  int d = int(a[222].real() + 0.5);
  FFT::FFT(n, b.data());
  FFT::FFT(n, b.data(), true);
  if (d == int(b[222].real() + 0.5)) std::cout << "O";
  if (d == int(a[222].real() + 0.5)) std::cout << "O";
  std::cerr << "--\n";
  std::cerr << 200 * double(clock()) / CLOCKS_PER_SEC << " sec"
            << "\n";*/
  int q;
  cin >> q;
  while (q-- > 0) {
    int n;
    cin >> n;
    int s = 0;
    for (int i = 0; i < n; ++i) {
      cin >> w[i];
      s += w[i];
    }
    ++s;
    vi a(s);
    for (int i = 0; i < s; ++i) {
      cin >> a[i];
    }
    debug(a);
    vii al(n);
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      --a;
      --b;
      al[a].push_back(b);
      al[b].push_back(a);
    }
    dfs(0, al);
    double res = 0;
    double total_subtrees = 0;
    for (int i = 0; i < n; ++i) {
      debug(subtrees[i]);
      total_subtrees += subtrees[i];
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < (int)ans[i].size(); ++j) {
        res += subtrees[i] / total_subtrees * ans[i][j].real() * a[j];
      }
    }
    std::cout << std::fixed << std::setprecision(19);

    cout << res << "\n";
  }

  return 0;
}
