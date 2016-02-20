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
    if (!f)
      o << ", ";
    if (IsIterable__<decltype(x)>::value)
      o << "\n";
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

template <class V> void r(V &v) {
  for (auto &x : v) {
    cin >> x;
  }
}

void solve(vector<pii> &ans, int start, int vol, const vi &type, const vi &pos,
           vector<pii> fi) {
  sort(all(fi));
  for (int tt = 1; tt <= 3; ++tt) {
    // debug(tt);
    vector<pii> segs;
    segs.emplace_back(start, +1);
    segs.emplace_back(start + vol, -1);
    for (size_t i = 0; i < pos.size(); ++i) {
      if (type[i] >= tt && pos[i] >= start) {
        segs.emplace_back(pos[i], +1);
        segs.emplace_back(pos[i] + vol, -1);
      }
    }
    sort(all(segs));
    // debug(segs);
    int bal = 0;
    size_t j = 0;
    vi gaps(ans.size());
    int add = 0;
    for (size_t i = 0; i < fi.size(); ++i) {
      int x = fi[i].first;
      int ind = fi[i].second;
      if (i) {
        gaps[ind] = gaps[fi[i - 1].second] - add;
      }
      while (j < segs.size() && segs[j].first <= x) {
        if (bal == 0 && j > 0) {
          gaps[ind] += segs[j].first - segs[j - 1].first;
        }
        bal += segs[j].second;
        ++j;
      }
      if (bal == 0) {
        --j;
        add = x - segs[j].first;
        gaps[ind] += add;
        ++j;
      } else {
        add = 0;
      }
    }
    debug(gaps);
    for (size_t i = 0; i < fi.size(); ++i) {
      int ind = fi[i].second;
      if (tt == 1) {
        if (gaps[ind] > 0) {
          ans[ind] = pii(-1, -1);
        }
      }
      if (tt == 2) {
        if (ans[ind] != pii(-1, -1)) {
          ans[ind].first = gaps[ind];
        }
      }
      if (tt == 3) {
        if (ans[ind] != pii(-1, -1)) {
          ans[ind].second = gaps[ind] - ans[ind].first;
        }
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int e, s, n, m;
  cin >> e >> s >> n >> m;
  vi t(n);
  ;
  vi x(n);
  for (int i = 0; i < n; ++i) {
    cin >> t[i] >> x[i];
  }
  vi f(m);
  r(f);

  vector<pii> ans(m, pii(-2, -2));
  vector<pii> fi;
  for (int i = 0; i < m; ++i) {
    if (f[i] > e) {
      fi.emplace_back(f[i], i);
    }
  }
  solve(ans, e, s, t, x, fi);

  fi.clear();
  for (int i = 0; i < m; ++i) {
    if (f[i] == e) {
      ans[i] = pii(0, 0);
    }
    if (f[i] < e) {
      fi.emplace_back(-f[i], i);
    }
  }
  for (int &a : x) {
    a *= -1;
  }
  solve(ans, -e, s, t, x, fi);
  for (auto a : ans) {
    cout << a.first << " " << a.second << "\n";
  }

  return 0;
}
