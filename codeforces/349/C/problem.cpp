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

const int mod = 1000 * 1000 * 1000 + 7;

int mul(int x, int y) { return static_cast<int>((1LL * x * y) % mod); }
int add(int x, int y) { return (x + y) % mod; }

int mod_pow(int x, int n) {
  assert(n >= 0);
  int r = 1;
  while (n > 0) {
    if ((n & 1) != 0) {
      r = mul(r, x);
      --n;
    } else {
      x = mul(x, x);
      n /= 2;
    }
  }
  return r;
}

int inv(int x) {
  int i = mod_pow(x, mod - 2);
  assert(mul(i, x) == 1);
  return i;
}

int geom_sum(int r, int n) {
  return mul(add(mod - 1, mod_pow(r, n)), inv(add(mod - 1, r)));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int r = mul(25, inv(26));

  int q;
  cin >> q;
  string s;
  cin >> s;
  int n = static_cast<int>(s.size());

  debug(n);
  vector<pii> req;
  map<int, vi> req_given_n;

  while (q-- > 0) {
    int t;
    cin >> t;
    if (t == 1) {
      cin >> s;
      n = static_cast<int>(s.size());
    } else {
      int m;
      cin >> m;
      req.emplace_back(n, m);
      req_given_n[n].push_back((int)(req.size()) - 1);
    }
  }

  vi p26;
  vi p_r;
  vi f;
  vi ifa;
  for (int i = 0; i < 100 * 1000 + 100; ++i) {
    if (i == 0) {
      p26.push_back(1);
      p_r.push_back(1);
      f.push_back(1);
      ifa.push_back(1);
    } else {
      p26.push_back(mul(26, p26.back()));
      p_r.push_back(mul(r, p_r.back()));
      f.push_back(mul(i, f.back()));
      ifa.push_back(inv(f.back()));
    }
  }

  vi ans(req.size(), -1);
  for (auto kv : req_given_n) {
    vector<pii> m_seq;
    int n = kv.first;
    for (int i : kv.second) {
      int m = req[i].second;
      m_seq.emplace_back(m, i);
    }
    sort(all(m_seq));
    int j = 0;
    while (j < (int)m_seq.size() && m_seq[j].first < n) {
      int index = m_seq[j].second;
      ans[index] = 0;
      ++j;
    }
    int cur = 1;
    for (int M = n; M <= 100 * 1000; ++M) {
      while (j < (int)m_seq.size() && m_seq[j].first == M) {
        int index = m_seq[j].second;
        ans[index] = cur;
        ++j;
      }
      if (j == (int)m_seq.size()) {
        break;
      }
      ++M;
      cur = mul(cur, 26);
      cur =
          add(cur,
              mul(p26[M - n],
                  mul(p_r[M - n], mul(f[M - 1], mul(ifa[n - 1], ifa[M - n])))));
      --M;
    }
  }
  for (int x : ans) {
    assert(x >= 0);
    cout << x << "\n";
  }

  return 0;
}
