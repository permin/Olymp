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

int gcd(int x, int y) {
  while (x) {
    y %= x;
    swap(x, y);
  }
  return y;
}

pii dir(const pii &origin, const pii &target) {
  int dx = target.first - origin.first;
  int dy = target.second - origin.second;
  int d = gcd(abs(dx), abs(dy));
  dx /= d;
  dy /= d;
  return pii(dx, dy);
}

ll sqr(int x) { return 1LL * x * x; }

ll dist(const pii &a, const pii &b) {
  return sqr(a.first - b.first) + sqr(a.second - b.second);
}

struct ShootPosInfo {
  vector<int> group_id;
  vector<vector<int>> groups;

  static ShootPosInfo build(const vector<pii> &monsters, const pii &origin) {
    map<pii, vector<int>> g;
    for (int i = 0; i < (int)monsters.size(); ++i) {
      g[dir(origin, monsters[i])].push_back(i);
    }
    ShootPosInfo res;
    res.group_id.resize(monsters.size());
    for (const auto &kv : g) {
      res.groups.push_back(kv.second);
      for (int i : kv.second) {
        res.group_id[i] = int(res.groups.size()) - 1;
      }
      std::sort(all(res.groups.back()), [&](int m1, int m2) {
        return dist(origin, monsters[m1]) < dist(origin, monsters[m2]);
      });
    }
    return res;
  }
};

vector<ShootPosInfo> infos;

vector<bool> killed;

typedef std::bitset<1000> Set;
int n, k;

void rec(int avialable_pos, Set &dead) {
  if (avialable_pos == 0) {
    return;
  }
  for (int i = 0; i < k; ++i) {
    if (avialable_pos & (1 << i)) {
      const auto &info = infos[i];
      for (const auto &group : info.groups) {
        for (int j = 0; j < (int)group.size() && j <= k; ++j) {
          int m = group[j];
          if (!dead[m]) {
            dead[m] = 1;
            rec(avialable_pos ^ (1 << i), dead);
            killed[m] = true;
            dead[m] = 0;
            break;
          }
        }
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin >> k >> n;
  vector<pii> stones_pos(k);
  for (int i = 0; i < k; ++i) {
    cin >> stones_pos[i].first >> stones_pos[i].second;
  }
  vector<pii> monsters(n);
  for (int i = 0; i < n; ++i) {
    cin >> monsters[i].first >> monsters[i].second;
  }
  for (int i = 0; i < k; ++i) {
    infos.emplace_back(ShootPosInfo::build(monsters, stones_pos[i]));
  }
  killed.assign(n, 0);
  Set dead;
  rec((1 << k) - 1, dead);
  cout << std::count(all(killed), true) << "\n";

  return 0;
}
