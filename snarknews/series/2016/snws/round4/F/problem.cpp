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

struct Dummy {
  explicit Dummy(int n) {
    this->n = n;
    s = rand() % n;
    shift = rand() % n;
    counter = 0;
  }

  int ask_n() { return n; }

  int ask_s() { return s; }

  int get_c(int i) {
    int r = (shift + i) % n;
    ++counter;
    assert(counter <= 30);

    return r;
  }

  int n;
  int s;

  int shift;
  int counter;
};

struct IO {
  IO() { cin >> n >> s; }
  int ask_s() { return s; }
  int ask_n() { return n; }
  int get_c(int i) {
    cout << i + 1 << endl;
    int x;
    cin >> x;
    return x;
  }
  int n, s;
};

// typedef Dummy Interactor;
typedef IO Interactor;

bool solve(Interactor &interactor) {
  int n = interactor.ask_n();
  int s = interactor.ask_s();

  int L = 0;
  int v0 = interactor.get_c(L);
  if (v0 == s) {
    return true;
  }
  int dir = s > v0 ? +1 : -1;

  debug(s);
  debug(L);
  debug(dir);
  debug(v0);

  for (int p2 = 28; p2 >= 0; --p2) {
    if ((1 << p2) >= n) {
      continue;
    }
    int R = (((L + dir * (1 << p2)) % n) + n) % n;
    int v = interactor.get_c(R);

    debug(R);
    debug(v);

    if (dir == +1 && v < v0) {
      continue;
    }
    if (dir == -1 && v > v0) {
      continue;
    }
    if (v == s) {
      return true;
    }
    if (v < s && dir == +1) {
      L = R;
      v0 = v;
    }
    if (v > s && dir == -1) {
      L = R;
      v0 = v;
    }
    debug(L);
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  IO i;
  solve(i);

  /*while (true) {
    Dummy d(100 * 1000 * 1000);
    assert(solve(d));
    cerr << ".\n";
  }*/

  return 0;
}
