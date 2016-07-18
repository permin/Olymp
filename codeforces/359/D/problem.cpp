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
int k;

void solve1d(const vector<int> &y, vector<int> &ans) {
  int min_right = -INF;
  int n = (int)y.size();
  int i = 0;
  int j = 0;
  while (i < n) {
    j = max(i, j);
    min_right = max(min_right, y[i]);
    if (i > 0) {
      min_right = max(min_right, y[i - 1] + k);
    }
    while (true) {
      bool ch = 0;
      while (j < n && y[j] <= min_right) {
        ++j;
      }
      int max_right = min(y[i] + k - 1, j == n ? INF : y[j] - 1);
      if (max_right >= min_right) {
        ans[j - i] += max_right - min_right + 1;
        min_right = max_right + 1;
        ch = 1;
      }
      if (!ch) {
        break;
      }
    }
    int i_ = i;
    while (i_ < n && y[i] == y[i_]) {
      ++i_;
    }
    i = i_;
  }
}

void solve1dst(const vi &y, vi &ans) {
  for (int a = -10000; a <= +10000; ++a) {
    int c = 0;
    for (int z : y) {
      if (a <= z && z <= a + k - 1) {
        ++c;
      }
    }
    if (c > 0) {
      ans[c] += 1;
    }
  }
}

void ss() {
  while (true) {
    vi y;
    int n = 20;
    for (int i = 0; i < n; ++i) {
      y.push_back(rand() % 1000);
    }
    sort(all(y));
    k = 3;
    vi a1(n + 1);
    vi a2(n + 1);
    solve1d(y, a1);
    solve1dst(y, a2);
    debug(y);
    debug(a1);
    debug(a2);
    assert(a1 == a2);
    debug('.');
  }
}

struct Point {
  int x, y, index;
};
void upd_same_x(int &i, const vector<Point> &p) {
  int i_ = i;
  while (i_ < (int)p.size() && p[i_].x == p[i].x) {
    ++i_;
  }
  i = i_;
}

struct CompareByX {
  bool operator()(const Point &p1, const Point &p2) const {
    return make_tuple(p1.x, p1.y, p1.index) < make_tuple(p2.x, p2.y, p2.index);
  }
};
struct CompareByY {
  bool operator()(const Point &p1, const Point &p2) const {
    return make_tuple(p1.y, p1.x, p1.index) < make_tuple(p2.y, p2.x, p2.index);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n >> k;
  vector<Point> points;
  for (int i = 0; i < n; ++i) {
    Point P;
    cin >> P.x;
    cin >> P.y;
    P.index = -1;
    points.push_back(P);
  }
  sort(all(points), CompareByX());
  for (int i = 0; i < n; ++i) {
    points[i].index = i;
  }
  int i = 0;
  int j = 0;
  vector<Point> in_coridor;
  while (j < n && points[j].x <= points[i].x + k - 1) {
    in_coridor.push_back(points[j]);
    ++j;
  }
  sort(all(in_coridor), CompareByY());

  vi ans(n + 1);
  do {
    auto it = remove_if(all(in_coridor), [&](const Point &p1) {
      return p1.x > points[i].x + k - 1;
    });
    in_coridor.erase(it, in_coridor.end());
    vector<Point> new_portion;
    while (j < n && points[j].x <= points[i].x + k - 1) {
      new_portion.push_back(points[j]);
      ++j;
    }
    sort(all(new_portion), CompareByY());
    vector<Point> new_in_coridor(new_portion.size() + in_coridor.size());
    std::merge(all(new_portion), all(in_coridor), new_in_coridor.begin(),
               CompareByY());
    new_in_coridor.swap(in_coridor);
    vi ys;
    for (auto e : in_coridor) {
      ys.push_back(e.y);
    }
    debug(ys);
    solve1d(ys, ans);
    upd_same_x(i, points);
  } while (i < n);
  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << " ";
  }
  cout << "\n";
  return 0;
}
