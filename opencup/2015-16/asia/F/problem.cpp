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

struct Color {
  int min = INF;
  int max = -INF;
};

int cache[20];
int cache_valid_untill[20];

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<int> color;
  vector<int> value;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    value.push_back(x);
    color.push_back(y);
  }
  int colors_number = 0;
  vi unique_colors = color;
  sort(all(unique_colors));
  colors_number = static_cast<int>(
      std::distance(unique_colors.begin(), std::unique(all(unique_colors))));
  unique_colors.resize(colors_number);
  if (colors_number == 1) {
    cout << "-1\n";
    return 0;
  }

  vector<Color> colors(colors_number);
  for (int i = 0; i < n; ++i) {
    int c = static_cast<int>(lower_bound(all(unique_colors), color[i]) -
                             unique_colors.begin());
    colors[c].min = min(colors[c].min, value[i]);
    colors[c].max = max(colors[c].max, value[i]);
  }
  sort(all(colors),
       [](const Color &c1, const Color &c2) { return c1.min < c2.max; });
  for (int i = 0; i < colors_number; ++i) {
    cerr << colors[i].min << " " << colors[i].max << "\n";
  }
  int M = INF;
  for (int i = 0; i + 1 < colors_number; ++i) {
    if (colors[i].max >= colors[i + 1].min) {
      cout << "0\n";
      return 0;
    }
  }
  M = min(M, colors[1].min - 1);
  for (int i = 0; i + 2 < colors_number; ++i) {
    M = min(M, colors[i + 2].min - colors[i].max - 1);
  }

  int res = 0;

  for (int m = 1; m <= M && m < 1000 * 1000; ++m) {
    int prev_value = -1;
    bool ok = 1;
    for (int i = 0; i < colors_number; ++i) {
      int value = -1;
      value = (colors[i].min + m - 1) / m;
      int max_value = (colors[i].max + m - 1) / m;
      if (value != max_value) {
        ok = 0;
      }
      if (value == prev_value) {
        ok = false;
        break;
      }
      prev_value = value;
    }
    res += ok;
  }

  for (int m = 1000 * 1000; m <= M; ++m) {
    int prev_value = -1;
    bool ok = 1;
    for (int i = 0; i < colors_number; ++i) {
      int value = -1;
      if (cache_valid_untill[i] > m) {
        value = cache[i];
      } else {
        value = (colors[i].min + m - 1) / m;
        int max_value = (colors[i].max + m - 1) / m;
        if (value != max_value) {
          m = max(m, (colors[i].max - 1) / value);
          ok = 0;
          break;
        } else {
          cache[i] = value;
          if (colors[i].min == 1)
            cache_valid_untill[i] = INF;
          else {
            if (value > 2) {
              cache_valid_untill[i] = (colors[i].min + 1) / (value - 2);
            }
          }
        }
      }
      if (value == prev_value) {
        ok = false;
        break;
      }
      prev_value = value;
    }
    int m_ = *min_element(&cache_valid_untill[0],
                          &cache_valid_untill[colors_number]);
    debug(cache_valid_untill[0]);
    debug(cache_valid_untill[1]);
    debug(m);
    debug(m_);
    if (ok) {
      if (m_ > m) {
        res += m_ - m;
        m = m_ - 1;

      } else {
        ++res;
      }
    } else {
      if (m_ > m) {
        m = m_ - 1;
      }
    }
  }
  cout << res << "\n";

  return 0;
}
