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

vector<int> primes;
vii values;
vector<int> prime_id;

vector<int> factor(int n) {
  vi r;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      r.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    r.push_back(n);
  }
  return r;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vi a(n);
  prime_id.resize(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    int k = i + 1;
    if (a[i] >= k) {
      cout << "0\n";
      return 0;
    }
  }
  debug(n);
  {
    for (int i = 2; i <= n; ++i) {
      bool ok = true;
      for (int j = 2; j * j <= i; ++j) {
        if (i % j == 0) {
          ok = false;
          break;
        }
      }
      if (ok) {
        primes.push_back(i);
        prime_id[i] = primes.size() - 1;
        values.emplace_back();
        int m = n / i;
        while (m) {
          values.back().push_back(-1);
          m /= i;
        }
      }
    }
  }
  debug(primes);
  for (int i = 0; i < n; ++i) {
    if (a[i] == -1) {
      continue;
    }
    vi fs = factor(i + 1);
    for (int p : fs) {
      int j = prime_id[p];
      size_t k = i + 1;
      size_t pw = 0;
      int p_pw = 1;
      while (k % primes[j] == 0) {
        int old_value = values[j][pw];
        values[j][pw] = (a[i] / p_pw) % primes[j];
        if (old_value >= 0 && values[j][pw] != old_value) {
          cout << 0 << "\n";
          return 0;
        }
        k /= primes[j];
        ++pw;
      }
    }
  }
  debug(values);
  ll res = 1;
  const ll mod = 1000 * 1000 * 1000 + 7;
  for (size_t i = 0; i < primes.size(); ++i) {
    for (size_t j = 0; j < values[i].size(); ++j) {
      if (values[i][j] == -1) {
        res = (res * primes[i]) % mod;
      }
    }
  }
  cout << res << "\n";

  return 0;
}
