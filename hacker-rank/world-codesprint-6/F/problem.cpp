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

set<int> sums;
set<int> remains;
vector<int> matched_with;
int used[1000];

vi best_matched;
size_t sums_size = 0;

int n = 5;
int guess_ans();
void rec(int second) {
  if (second > n) {
    if (sums.size() > sums_size) {
      sums_size = sums.size();
      best_matched = matched_with;
      if ((int)sums_size == guess_ans()) {
        throw 1;
      }
    }
    return;
  }
  for (int x = 0; x <= guess_ans(); ++x) {
    if (used[x]) {
      continue;
    }
    int new_sum = x + second;
    if (new_sum > n) {
      continue;
    }
    if (sums.count(new_sum) == 0) {
      used[x] = 1;
      remains.erase(x);
      matched_with.push_back(x);
      sums.insert(new_sum);
      rec(second + 1);
      sums.erase(new_sum);
      matched_with.pop_back();
      remains.insert(x);
      used[x] = 0;
    }
  }
  {
    matched_with.push_back(-1);
    rec(second + 1);
    matched_with.pop_back();
  }
}

int guess_ans() {
  vi a;
  int i = 1;
  while (int(a.size()) < n + 1) {
    a.push_back(i);
    if (i & 1) {
      a.push_back(i);
    }
    ++i;
  }
  return a[n];
}

int st_solve() {
  int res = 0;
  int m = guess_ans();
  vi x;
  vi y;
  for (int i = 0; i < m; ++i) {
    x.push_back(i);
    y.push_back(-1);
  }
  {
    int i = 0;
    int p = (int)y.size() - 1;
    while (i < m) {
      y[p] = i;
      i += 2;
      --p;
    }
    i = 1;
    while (i < m) {
      y[p] = i;
      i += 2;
      --p;
    }
  }

  if (n % 3 == 2) {
    y[0] = n;
  }
  set<int> z;
  cout << m << "\n";
  for (int i = 0; i < m; ++i) {
    int zz = n - x[i] - y[i];
    assert(zz >= 0);
    assert(z.count(zz) == 0);
    z.insert(zz);
    cout << x[i] << " " << y[i] << " " << zz << "\n";
  }
  exit(0);

  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin >> n;
  st_solve();
  return 0;
  try {
    rec(0);
  } catch (...) {
  }
  debug(n);
  debug(sums_size);
  assert(sums_size == guess_ans());
  debug(best_matched);
  for (int i = 0; i <= n; ++i) {
    if (best_matched[i] != -1) {
      cout << i << " " << best_matched[i] << " " << n - (i + best_matched[i])
           << "\n";
    }
  }
  return 0;
}
