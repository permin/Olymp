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
const long long LLINF = std::numeric_limits<ll>::max() / 2;

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

string dir;

vector<vector<pii>> al;

void add_edge(int from, int to, int len) {
  al[from].emplace_back(to, len);
  debug(from);
  debug(to);
  debug(len);
  // al[to].emplace_back(from, len);
}

template <class It> void process(It begin, It end, char d) {
  It last_d = end;
  for (It it = begin; it != end; ++it) {

    if (last_d != end) {
      add_edge(last_d->second, it->second, abs(it->first - last_d->first));
    }
    if (dir[it->second] == d) {
      last_d = it;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  ll t;
  cin >> n >> t;
  vi x(n);
  vi y(n);
  dir.assign(n, '?');
  map<int, vector<pii>> group_x;
  map<int, vector<pii>> group_y;
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> y[i] >> dir[i];
    group_x[x[i]].emplace_back(y[i], i);
    group_y[y[i]].emplace_back(x[i], i);
  }

  al.resize(n);

  for (auto row : group_y) {
    sort(all(row.second));
    debug(row.second);
    process(all(row.second), 'R');
    process(row.second.rbegin(), row.second.rend(), 'L');
  }
  for (auto col : group_x) {
    sort(all(col.second));
    debug(col.second);
    process(all(col.second), 'U');
    process(col.second.rbegin(), col.second.rend(), 'D');
  }

  vector<ll> dist(n, LLINF);
  typedef pair<ll, int> Key;
  set<Key> Q;
  Q.insert(Key(0, 0));
  dist[0] = 0;
  debug(al);
  while (!Q.empty()) {
    int v = Q.begin()->second;
    Q.erase(Q.begin());
    for (auto v2_len : al[v]) {
      int v2 = v2_len.first;
      ll len = v2_len.second;
      ll cur_dist = dist[v] + len;
      if (cur_dist <= dist[v2]) {
        Q.erase(Key(dist[v2], v2));
        dist[v2] = cur_dist;
        Q.insert(Key(dist[v2], v2));
      }
    }
  }
  debug(dist);

  for (int i = 0; i < n; ++i) {
    if (dist[i] >= LLINF) {
      cout << x[i] << " " << y[i] << "\n";
    } else {
      ll moved = t - dist[i];
      if (moved < 0) {
        cout << x[i] << " " << y[i] << "\n";
      } else {
        ll dx = 0;
        ll dy = 0;
        if (dir[i] == 'L') {
          --dx;
        }
        if (dir[i] == 'R') {
          ++dx;
        }
        if (dir[i] == 'U') {
          ++dy;
        }
        if (dir[i] == 'D') {
          --dy;
        }
        cout << x[i] + dx * moved << " " << y[i] + dy * moved << "\n";
      }
    }
  }

  return 0;
}
