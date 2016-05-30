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

vector<pii> points;

const int M = 100 * 1000 * 1000 + 2;
vector<pii> ans;
int dist;

vector<pii> rec_corners(int x, int y, int dx, int dy) {
  vector<pii> res;
  res.reserve(4);
  res.emplace_back(x, y);
  res.emplace_back(x + dx, y);
  res.emplace_back(x, y + dy);
  res.emplace_back(x + dx, y + dy);
  return res;
}

void solve(const vector<pii> &corners) {
  vi p = {0, 1, 2, 3};
  vector<pii> cand(4);
  do {
    bool ok = 1;
    int d2 = 0;
    for (int i = 0; i < 4; ++i) {
      cand[i] = corners[p[i]];
      if (points[i].first != cand[i].first &&
          points[i].second != cand[i].second) {
        ok = 0;
        break;
      }
      int d = 0;
      d += abs(points[i].first - cand[i].first);
      d += abs(points[i].second - cand[i].second);
      d2 = max(d2, d);
    }
    if (ok && dist > d2) {
      dist = d2;
      ans = cand;
    }
  } while (next_permutation(all(p)));
}

void sort_uniq(vi &a) {
  sort(all(a));
  a.erase(unique(all(a)), a.end());
}

void solve() {
  points.resize(4);
  vi x;
  vi y;
  for (int i = 0; i < 4; ++i) {
    cin >> points[i].first;
    cin >> points[i].second;
    points[i].first += M;
    points[i].second += M;
    x.push_back(points[i].first);
    y.push_back(points[i].second);
  }
  sort(all(x));
  sort(all(y));
  sort_uniq(x);
  sort_uniq(y);
  vi sides;
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      sides.push_back(x[j] - x[i]);
      sides.push_back(y[j] - y[i]);
    }
  }

  dist = INF;
  sort_uniq(sides);
  for (int s : sides) {
    if (s == 0) {
      continue;
    }
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int dx = -1; dx <= +1; dx += 2) {
          for (int dy = -1; dy <= +1; dy += 2) {
            solve(rec_corners(x[i], y[j], dx * s, dy * s));
            for (int k = 0; k < 4; ++k) {
              solve(rec_corners((x[i] + x[k] - s) / 2, y[j], dx * s, dy * s));
              solve(
                  rec_corners((x[i] + x[k] - s + 1) / 2, y[j], dx * s, dy * s));
              solve(
                  rec_corners((x[i] + x[k] - s - 1) / 2, y[j], dx * s, dy * s));

              solve(rec_corners(x[j], (y[i] + y[k] - s) / 2, dx * s, dy * s));
              solve(
                  rec_corners(x[j], (y[i] + y[k] - s + 1) / 2, dx * s, dy * s));
              solve(
                  rec_corners(x[j], (y[i] + y[k] - s - 1) / 2, dx * s, dy * s));
            }
          }
        }
      }
    }
  }
  debug(sides);
  if (dist == INF) {
    cout << "-1\n";
  } else {
    cout << dist << "\n";
    for (int i = 0; i < 4; ++i) {
      cout << ans[i].first - M << " ";
      cout << ans[i].second - M << "\n";
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  cin >> t;
  while (t-- > 0) {
    solve();
  }

  return 0;
}
