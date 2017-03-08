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

const int maxN = 5 * 1000 * 10 + 10;
typedef unordered_map<ll, int> Map;

Map stat[maxN];
ll subtree[maxN];
ll subtree_size[maxN];

void SWAP(Map &a, Map b) {
  if (&a != &b) {
    a.swap(b);
  }
}

Map &merge_maps(Map &a, Map &b) {
  /*if (a.size() > b.size()) {
    a.swap(b);
  }*/
  for (const auto &kv : a) {
    b[kv.first] += kv.second;
  }
  a.clear();
  return b;
}

ll ans;
ll total_coins;
Map total_stat;

void dfs1(int v, const vii &al, const vi &c, int p = -1) {
  subtree[v] = c[v];
  subtree_size[v] = 1;
  for (int v2 : al[v]) {
    if (v2 == p) {
      continue;
    }
    dfs1(v2, al, c, v);
    subtree[v] += subtree[v2];
    subtree_size[v] += subtree_size[v2];
  }
  if (subtree[v] * 2 == total_coins) {
    ans = min(ans, total_coins / 2);
  }
}

void dfs2(int v, const vii &al, const vi &c, int p = -1) {
  stat[v].clear();
  int elements = 0;
  for (int v2 : al[v]) {
    if (v2 == p) {
      continue;
    }
    dfs2(v2, al, c, v);
    if (elements < subtree_size[v2]) {
      SWAP(stat[v], merge_maps(stat[v], stat[v2]));
    } else {
      SWAP(stat[v], merge_maps(stat[v2], stat[v]));
    }
    elements += subtree_size[v2];
  }
  ll C = subtree[v];
  stat[v][C] += 1;

  if (3 * C >= total_coins) {
    if (total_stat.count(C) && total_stat[C] >= 2) {
      ans = min(ans, 3 * C - total_coins);
    }
    ll C_ = total_coins - 2 * C;
    if (total_stat.count(C) && total_stat.count(C_) &&
        (stat[v].count(C_) == 0 || total_stat[C_] > stat[v][C_])) {
      ans = min(ans, 3 * C - total_coins);
    }
  }
  if ((C % 2 == 0) && (3 * (C / 2) >= total_coins)) {
    if (stat[v].count(C / 2)) {
      ans = min(ans, 3 * (C / 2) - total_coins);
    }
  }
  ll C1 = total_coins - C;
  if (C1 * 3 >= total_coins) {
    if (stat[v].count(C1) || stat[v].count(total_coins - 2 * C1)) {
      ans = min(ans, 3 * C1 - total_coins);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int q;
  cin >> q;
  while (q-- > 0) {
    int n;
    cin >> n;
    vector<int> c(n);
    total_coins = 0;
    for (int &a : c) {
      cin >> a;
      total_coins += a;
    }
    vii al(n);
    for (int i = 0; i + 1 < n; ++i) {
      int a, b;
      cin >> a >> b;
      --a;
      --b;
      al[a].push_back(b);
      swap(a, b);
      al[a].push_back(b);
    }
    ans = LLINF;
    dfs1(0, al, c);
    total_stat.clear();
    for (int i = 0; i < n; ++i) {
      total_stat[subtree[i]] += 1;
    }
    dfs2(0, al, c);
    if (ans >= LLINF) {
      ans = -1;
    }
    cout << ans << "\n";
  }

  return 0;
}
