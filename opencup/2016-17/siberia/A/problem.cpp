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

const int N = 10000 * 1000 + 8;
std::bitset<N> was;
int sd[N];

template <class It>
void rec(int d, It b, It e, vi &res) {
  res.push_back(d);
  if (b == e) {
    return;
  }
  int mul = b->first;
  int num = b->second;
  for (int i = 0; i <= num; ++i) {
    rec(d, std::next(b), e, res);
    if (i != num) {
      d *= mul;
    }
  }
}

vi divisors(int n) {
  debug(n);
  map<int, int> f;
  while (sd[n]) {
    f[sd[n]] += 1;
    n /= sd[n];
  }
  if (n > 1) {
    f[n] += 1;
  }
  debug(f);
  vi res;
  rec(1, f.begin(), f.end(), res);
  debug(res);
  return res;
}

int main() {
  {
    sd[1] = sd[0] = 0;
    for (int i = 2; i < N; ++i) {
      if (sd[i]) {
        continue;
      }
      int j = i + i;
      while (j < N) {
        if (sd[j] == 0) {
          sd[j] = i;
        } else {
          sd[j] = min(sd[j], i);
        }
        j += i;
      }
    }
  }
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vi a(n);
  for (int &x : a) {
    cin >> x;
  }
  sort(all(a));
  reverse(all(a));
  vi ans;
  for (int x : a) {
    if (was[x]) {
      continue;
    }
    ans.push_back(x);

    /*{
      auto d1 = divisors(x);
      vi d2;
      for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
          d2.push_back(x / i);
          d2.push_back(i);
        }
      }
      sort(all(d1));
      sort(all(d2));
      d1.erase(unique(all(d1)), d1.end());
      d2.erase(unique(all(d2)), d2.end());
      debug(d1);
      debug(d2);
      assert(d1 == d2);
    }*/
    for (int y : divisors(x)) {
      was[y] = true;
    }
  }
  sort(all(ans));
  for (int x : ans) {
    cout << x << " ";
  }
  cout << "\n";
  return 0;
}
