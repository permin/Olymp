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

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  vii tal(n);
  vii al(n);
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    tal[b].push_back(a);
    al[a].push_back(b);
  }
  vi pos(n, -1);
  vi order(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    --x;
    pos[x] = i;
    order[i] = x;
  }

  set<int> unchecked;
  for (int suffix = n - 1; suffix >= 0; --suffix) {
    vector<int> to_remove;
    for (auto it = unchecked.lower_bound(order[suffix]); it != unchecked.end();
         ++it) {
      bool ok = true;
      for (int v2 : tal[*it]) {
        int p = pos[v2];
        if (p < suffix) {
          continue;
        }
        ok = false;
        break;
      }
      if (ok) {
        swap(order[suffix], order[pos[*it]]);
        set<int> interesting(order.begin() + suffix + 1, order.end());
        set<pii> incoming;
        vi degs(n);
        for (int i = 0; i < n; ++i) {
          if (interesting.count(i) == 0) {
            continue;
          }
          int d = 0;
          for (int v2 : tal[i]) {
            if (interesting.count(v2) == 1) {
              ++d;
            }
          }
          degs[i] = d;
          incoming.emplace(d, i);
        }
        auto out_it = order.begin() + suffix + 1;
        while (!incoming.empty()) {
          pii deg_i = *incoming.begin();
          incoming.erase(incoming.begin());
          assert(deg_i.first == 0);
          *out_it = deg_i.second;
          ++out_it;
          for (int v2 : al[deg_i.second]) {
            if (interesting.count(v2) == 1) {
              incoming.erase(pii(degs[v2], v2));
              --degs[v2];
              incoming.insert(pii(degs[v2], v2));
            }
          }
        }
        assert(out_it == order.end());
        for (int i = 0; i < n; ++i) {
          cout << order[i] + 1 << " ";
        }
        cout << "\n";

        return 0;
      }
      to_remove.push_back(*it);
    }
    for (int x : to_remove) {
      unchecked.erase(x);
    }
    unchecked.insert(order[suffix]);
  }
  cout << "-1\n";
  return 0;
}
