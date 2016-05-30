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

bool bad(const vi &a) { return a.size() == 1 && a[0] == -1; }

vi solve(const vii &red, const vii &blue) {
  vi ans;
  size_t n = red.size();
  vector<int> label(n, -1);
  for (size_t v = 0; v < n; ++v) {
    if (label[v] >= 0) {
      continue;
    }
    vector<size_t> comp;
    queue<size_t> Q;
    label[v] = 0;
    Q.push(v);
    while (!Q.empty()) {
      size_t v2 = Q.front();
      comp.push_back(v2);
      Q.pop();
      for (size_t v3 : red[v2]) {
        if (label[v3] == -1) {
          label[v3] = 1 - label[v2];
          Q.push(v3);
        }
      }
      for (size_t v3 : blue[v2]) {
        if (label[v3] == -1) {
          label[v3] = label[v2];
          Q.push(v3);
        }
      }
    }
    size_t one = 0;
    size_t zero = 0;
    for (size_t v2 : comp) {
      if (label[v2] == 1) {
        ++one;
      } else {
        ++zero;
      }
      for (size_t v3 : red[v2]) {
        if (label[v2] == label[v3]) {
          return {-1};
        }
      }
      for (size_t v3 : blue[v2]) {
        if (label[v2] != label[v3]) {
          return {-1};
        }
      }
    }
    int t = 0;
    if (one < zero) {
      t = 1;
    }
    for (size_t v2 : comp) {
      if (label[v2] == t) {
        ans.push_back(static_cast<int>(v2));
      }
    }
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  int m;
  cin >> n >> m;
  vii blue(n);
  vii red(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    string c;
    cin >> c;
    if (c == "R") {
      red[x].push_back(y);
      red[y].push_back(x);
    } else {
      blue[x].push_back(y);
      blue[y].push_back(x);
    }
  }
  vi ans = {-1};
  for (int i = 0; i < 2; ++i) {
    vi cur = solve(blue, red);
    if (!bad(cur)) {
      if (bad(ans) || ans.size() > cur.size()) {
        ans = cur;
      }
    }
    swap(blue, red);
  }
  if (bad(ans)) {
    cout << "-1\n";
  } else {
    cout << ans.size() << "\n";
    sort(all(ans));
    for (int x : ans) {
      cout << x + 1 << " ";
    }
    cout << "\n";
  }

  return 0;
}
