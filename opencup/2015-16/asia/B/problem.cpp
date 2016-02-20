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
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

const int M = 10002;
const int MAX_ABS = 10 * M;
const int SIZE = MAX_ABS * 2 + 4;
int data[SIZE][2];
bool is_interesting[SIZE][2];

const int kOdd = 0;
const int kEven = 1;

// int interesting;

int get(int x, int odd_even) {
  assert(abs(x) <= MAX_ABS);
  assert(0 <= odd_even && odd_even <= 1);
  return data[MAX_ABS + x][odd_even];
}

void setValue(int x, int odd_even, int val) {
  assert(abs(x) <= MAX_ABS);
  assert(0 <= odd_even && odd_even <= 1);
  /*if (is_interesting[MAX_ABS + x][odd_even])
    --interesting;*/
  // assert(interesting >= 0);
  data[MAX_ABS + x][odd_even] = val;
}

/*void setInter(int x, int odd_even) {
  assert(abs(x) <= MAX_ABS);
  assert(0 <= odd_even && odd_even <= 1);
  if (is_interesting[MAX_ABS + x][odd_even])
    return;
  ++interesting;
  is_interesting[MAX_ABS + x][odd_even] = 1;
}*/

int gcd(int x, int y) {
  while (x > 0) {
    y %= x;
    swap(x, y);
  }
  return y;
}

void init() { memset(data, -1, sizeof(data)); }

int main() {
  init();

  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int d = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i] < a[j]) {
        d = gcd(d, 2 * (a[j] - a[i]));
      }
    }
  }

  /*for (int k = -M; k <= M; ++k) {
    if ((d > 0 && abs(k) % d == 0) || (d == 0 && k == 0)) {
      setInter(k, kEven);
    }
  }
  for (int k = -3 * M; k <= 2 * M; ++k) {
    if ((d > 0 && abs(k) % d == 0) || (d == 0 && k == 0)) {
      for (int m : a) {
        int x = 2 * m + k;
        if (-M <= x && x <= M) {
          setInter(x, kOdd);
        }
      }
    }
  }*/

  setValue(0, kEven, 0);
  queue<pii> Q; // x even
  Q.push(pii(0, kEven));

  // interesting = INF / 2;

  while (!Q.empty()) { // && interesting > 0) {
    int val = Q.front().first;
    int parity = Q.front().second;
    Q.pop();

    for (int m : a) {
      int new_val = 2 * m - val;
      int new_parity = 1 - parity;
      if (abs(new_val) > MAX_ABS) {
        continue;
      }
      if (get(new_val, new_parity) != -1) {
        continue;
      }
      setValue(new_val, new_parity, get(val, parity) + 1);
      Q.push(pii(new_val, new_parity));
    }
  }

  // assert(interesting == 0);
  int q;
  cin >> q;
  while (q-- > 0) {
    int s, t;
    cin >> s >> t;
    int res = INF;
    if (get(s + t, kOdd) != -1) {
      res = get(s + t, kOdd);
    }
    if (get(t - s, kEven) != -1) {
      res = min(res, get(t - s, kEven));
    }
    if (res == INF)
      res = -1;
    cout << res << "\n";
  }

  return 0;
}
