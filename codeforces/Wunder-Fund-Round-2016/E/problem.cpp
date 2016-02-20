#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <valarray>

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

typedef std::complex<double> Complex;

struct Node {
  Complex sum = 0;
  bool is_delay = false;
  Complex delay;
};

class SegmentTree {
public:
  explicit SegmentTree(int n) {
    size_ = 1;
    while (size_ < n) {
      size_ *= 2;
}
    data_.resize(size_ * 2);
    build(0, size_, 1, n);
  }

  Complex sum(int l, int r) { return sum(l, r, 0, size_, 1); }

  void apply_mul(int l, int r, Complex mul) {
    apply_mul(l, r, mul, 0, size_, 1);
  }

private:
  void build(int tl, int tr, int id, int n) {
    if (tl + 1 == tr) {
      data_[id].sum = tl < n ? Complex(1) : Complex(0);
    } else {
      int tm = (tl + tr) / 2;
      build(tl, tm, id << 1, n);
      build(tm, tr, (id << 1) + 1, n);
      data_[id].sum = data_[id << 1].sum + data_[(id << 1) + 1].sum;
    }
  }

  void apply_mul(int l, int r, Complex mul, int tl, int tr, int id) {
    if (l <= tl && tr <= r) {
      if (static_cast<int>(data_[id].is_delay) == 0) {
        data_[id].is_delay = true;
        data_[id].delay = mul;
      } else {
        data_[id].delay *= mul;
      }
      data_[id].sum *= mul;
      return;
    }
    if (r <= tl || l >= tr) {
      return;
    }
    push(id, tl, tr);

    int tm = (tl + tr) / 2;
    apply_mul(l, r, mul, tl, tm, id << 1);
    apply_mul(l, r, mul, tm, tr, (id << 1) + 1);

    data_[id].sum = data_[id << 1].sum + data_[(id << 1) + 1].sum;
  }

  void push(int id, int tl, int tr) {
    if (data_[id].is_delay) {
      int tm = (tl + tr) / 2;
      apply_mul(tl, tm, data_[id].delay, tl, tm, (id << 1));
      apply_mul(tm, tr, data_[id].delay, tm, tr, (id << 1) + 1);
      data_[id].is_delay = false;
    }
  }

  Complex sum(int l, int r, int tl, int tr, int id) {
    if (l <= tl && tr <= r) {
      return data_[id].sum;
    }
    if (r <= tl || l >= tr) {
      return Complex(0);
    }
    push(id, tl, tr);
    int tm = (tl + tr) / 2;
    return sum(l, r, tl, tm, id << 1) + sum(l, r, tm, tr, (id << 1) + 1);
  }

  vector<Node> data_;
  int size_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  SegmentTree edges(n);
  int m;
  cin >> m;

  std::cout << std::setprecision(9);
  std::cout << std::fixed;
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    --y;
    if (x == 1) {
      Complex edge = edges.sum(y, y + 1);
      double len = std::abs(edge);
      edges.apply_mul(y, y + 1, Complex((len + z) / len));
    } else {
      double alpha = -2.0 * PI * z / 360;
      edges.apply_mul(y, n, Complex(cos(alpha), sin(alpha)));
    }
    Complex pos = edges.sum(0, n);
    cout << pos.real() << " " << pos.imag() << "\n";
  }

  return 0;
}
