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
template <class T, class V>
ostream &operator<<(ostream &o, const unordered_map<T, V> &v) {
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
int p;

int add(int x, int y) { return (x + y) % p; }
int mul(int x, int y) { return int((1LL * x * y) % p); }

int main() {
  std::ios_base::sync_with_stdio(false);
  unordered_map<int, int> L;
  unordered_map<int, int> L_ex;
  string s;
  cin >> s;
  int q;
  cin >> q >> p;
  int n = (int)s.size();
  {
    int m = 0;
    int p10 = 1;

    for (int i = n - 1; i >= 0; --i) {
      m = add(m, mul(s[i] - '0', p10));
      p10 = mul(p10, 10);
      L[m] += 1;
      L_ex[m] = i;
    }
  }
  vi x(q);
  for (int &y : x) {
    cin >> y;
  }
  auto M = x;

  /*vii stat(n, vi(n, -1));
  vi cor_ans(q);
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      stringstream o;
      o << s.substr(i, j - i + 1);
      ll m;
      o >> m;
      m %= p;
      stat[i][j] = (int)m;
      for (int k = 0; k < q; ++k) {
        if (m == M[k]) {
          cor_ans[k] += 1;
        }
      }
    }
  }*/

  vector<ll> a_1(q);
  vi a_2(q, -1);
  vi a_3(q, -1);
  int R = 0;
  int p10 = 1;
  for (int r = 0; r <= n - 1; ++r) {
    debug(L);
    for (int i = 0; i < q; ++i) {
      auto it = L.find(add(R, x[i]));
      if (it != L.end()) {
        a_1[i] += it->second;
        a_2[i] = L_ex[it->first];
        a_3[i] = n - 1 - r;
      }
      x[i] = mul(x[i], 10);
    }
    R = add(R, mul(p10, s[n - 1 - r] - '0'));
    p10 = mul(p10, 10);
    L[R] -= 1;
    assert(L[R] >= 0);
    if (L[R] == 0) {
      L.erase(R);
      L_ex.erase(R);
    }
  }

  // debug(cor_ans);
  debug(a_1);

  for (int i = 0; i < q; ++i) {
    // assert(a_1[i] == cor_ans[i]);
    //
    assert(a_1[i] || (a_2[i] == -1 && a_3[i] == -1));
    // assert(!a_1[i] || (stat[a_2[i]][a_3[i]] == M[i]));
    cout << a_1[i] << " " << a_2[i] + 1 << " " << a_3[i] + 1 << "\n";
  }

  return 0;
}
