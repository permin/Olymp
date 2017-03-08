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

int gcd(int x, int y) {
  while (x) {
    y %= x;
    swap(x, y);
  }
  return y;
}

void test(const vii &au, int B, int M) {
  return;
  for (int i = 0; i < M + M + M + M + B + B + B + B * B + 10; ++i) {
    int st = 0;
    int n = i;
    vi digs;
    while (n) {
      int d = n % B;
      n /= B;
      digs.push_back(d);
    }
    reverse(all(digs));
    for (int d : digs) {
      st = au[st][d];
    }
    debug(i);
    debug(i % M);
    debug(st);
    assert((st == 0) == (i % M == 0));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int B, M;
  cin >> B >> M;
  {
    vi classes(M, 1);
    classes[0] = 0;
    for (int i = 0; i < 12; ++i) {
      vector<pair<vi, int>> r(M);
      for (int x = 0; x < M; ++x) {
        r[x].first.push_back(classes[x]);
        r[x].second = x;
        r[x].first.reserve(B);
      }
      for (int d = 0; d < B; ++d) {
        for (int x = 0; x < M; ++x) {
          int to = (x * B + d) % M;
          r[x].first.push_back(classes[to]);
        }
      }
      sort(all(r));
      auto it = r.begin();
      vi new_classes(M, -1);
      int C = 0;
      while (it != r.end()) {
        auto it2 = it;
        debug(it->first);
        while (it2 != r.end() && it2->first == it->first) {
          ++it2;
        }
        for (auto it3 = it; it3 != it2; ++it3) {
          new_classes[it3->second] = C;
        }
        ++C;
        it = it2;
      }
      debug(r);
      classes = new_classes;
      debug(classes);
      if (C == 2) {
        break;
      }
    }
    debug(classes);
    int C = *max_element(all(classes));
    ++C;
    cout << C << " " << 0 << "\n";
    int F = classes[0];

    for (int i = 0; i < C; ++i) {
      if (i == F) {
        cout << "G ";
      } else {
        cout << "B ";
      }
    }
    cout << "\n";
    for (int i = 0; i < C; ++i) {
      int x = 0;
      while (classes[x] != i) ++x;
      for (int d = 0; d < B; ++d) {
        cout << classes[(x * B + d) % M] << " ";
      }
      cout << "\n";
    }

    return 0;
  }

  {
    vector<size_t> h(M, -1);
    map<size_t, int> rep;
    map<size_t, int> id;
    vector<size_t> cl;
    int C = 1;

    for (int x = 1; x < M; ++x) {
      size_t H = 0;
      int res = x;
      for (int i = 0; i < 1000; ++i) {
        res = (res * B) % M;
        H = H * (1000 * 1000 * 1000 + 7) + res;
      }
      if (id.count(H) == 0) {
        id[H] = C++;
        rep[H] = x;
        cl.push_back(H);
      }
      h[x] = H;
    }
    debug(h);
    cout << C << " " << 0 << "\n";
    for (int i = 0; i < C; ++i) {
      if (i == 0) {
        cout << "G ";
      } else {
        cout << "B ";
      }
    }
    cout << "\n";
    for (int i = 0; i < B; ++i) {
      int to = (0 * B + i) % M;
      if (to == 0) {
        cout << "0 ";
      } else {
        cout << id[h[to]] << " ";
      }
    }
    cout << "\n";

    vii au(C);
    {
      for (int i = 0; i < B; ++i) {
        int to = (0 * B + i) % M;
        if (to == 0) {
          au[0].push_back(0);
        } else {
          au[0].push_back(id[h[to]]);
        }
      }
      int CC = 1;
      for (size_t c : cl) {
        size_t res = c;
        for (int i = 0; i < B; ++i) {
          int to = (rep.at(res) * B + i) % M;
          if (to == 0) {
            au[CC].push_back(0);
          } else {
            au[CC].push_back(id.at(h.at(to)));
          }
        }
        ++CC;
      }
    }
    test(au, B, M);

    for (size_t c : cl) {
      size_t res = c;
      for (int i = 0; i < B; ++i) {
        int to = (rep.at(res) * B + i) % M;
        if (to == 0) {
          cout << "0 ";
        } else {
          cout << id.at(h.at(to)) << " ";
        }
      }
      cout << "\n";
    }

    /*if (gcd(B, M) == 1) {
      cout << M << " " << 0 << "\n";
      for (int i = 0; i < M; ++i) {
        if (i == 0) {
          cout << "G ";
        } else {
          cout << "B ";
        }
      }
      cout << "\n";
      for (int i = 0; i < M; ++i) {
        for (int j = 0; j < B; ++j) {
          cout << (i * B + j) % M << " ";
        }
        cout << "\n";
        //
      }
    } else {
      int d = gcd(B, M);
      int b = B / d;
      int m = M / d;
      cout << 2 * m << " " << 0 << "\n";
      for (int i = 0; i < 2 * m; ++i) {
        if (i == 0) {
          cout << "G ";
        } else {
          cout << "B ";
        }
      }
      for (int i = 0; i < 2 * m; ++i) {
        int mod = i < m ? i : i - m;
        for (int j = 0; j < B; ++j) {
          int res = (mod * b + j) % m;

        }
      }
    }*/
  }
  return 0;
}
