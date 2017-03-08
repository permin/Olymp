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
typedef vector<ll> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

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

const int A = 26;
int st[A];

const ll mul = 1 * 2 * 3 * 4;
const ll mod = mul * (1000 * 1000 * 1000 + 7);

ll C4(ll x) {
  ll res = x;
  res %= mod;
  res *= x - 1;
  res %= mod;
  res *= x - 2;
  res %= mod;
  res *= x - 3;
  res %= mod;
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  string s;
  cin >> s;
  string alpha(A, 0);

  int n = (int)s.size();
  debug(n);
  ll ans = 0;
  vii sa(A, vi(A));
  vii sba(A, vi(A));
  vii sbba(A, vi(A));
  for (int i = n - 1; i >= 0; --i) {
    // auto nsa = sa;
    // auto nsba = sba;
    // auto nsbba = sbba;
    for (int j = 0; j < A; ++j) {
      int k = s[i] - 'a';
      if (j == 0) {
        st[k] += 1;
      }
      if (j == k) continue;
      {
        int b = k;
        int a = j;
        // b
        sbba[a][b] += sba[a][b];
        sba[a][b] += sa[a][b];
        sbba[a][b] %= mod;
        sba[a][b] %= mod;
      }
      {
        int a = k;
        int b = j;
        // a
        ans += mul * sbba[a][b];
        ans %= mod;
        sa[a][b] += 1;
        sa[a][b] %= mod;
      }
    }
    // sa = nsa;
    // sba = nsba;
    // sbba = nsbba;
  }
  for (int i = 0; i < A; ++i) {
    int x = st[i];
    ans += C4(x);
    ans %= mod;
  }
  assert(ans % mul == 0);
  cout << (ans % mod) / mul << "\n";
  return 0;
}
