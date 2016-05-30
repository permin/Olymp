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
  vi signs;
  string s;
  cin >> s;
  signs.push_back(+1);
  while (true) {
    cin >> s;
    if (s == "=") {
      break;
    }
    if (s == "+") {
      signs.push_back(+1);
    } else {
      signs.push_back(-1);
    }
    cin >> s;
    assert(s == "?");
  }
  int n;
  cin >> n;
  if (signs.size() == 1) {
    cout << "Possible\n";
    cout << n << " = " << n << "\n";
    return 0;
  }

  vector<int> seq;
  int sum = 0;
  for (size_t i = 0; i < signs.size(); ++i) {
    seq.push_back(1 + (rand() % n));
    if (signs[i] == +1) {
      sum += seq.back();
    } else {
      sum -= seq.back();
    }
  }
  int it = 0;
  const int MAX = 1000 * 1000 * 10;
  while (sum != n) {
    ++it;
    if (it == MAX) {
      break;
    }
    int d = sum - n;
    size_t pos = rand() % signs.size();
    sum -= signs[pos] * seq[pos];
    if (d > 0) {
      if (signs[pos] == +1) {
        seq[pos] -= d;
      } else {
        seq[pos] += d;
      }
    } else {
      if (signs[pos] == +1) {
        seq[pos] -= d;
      } else {
        seq[pos] += d;
      }
    }
    if (seq[pos] < 1) {
      seq[pos] = 1;
    }
    if (seq[pos] > n) {
      seq[pos] = n;
    }
    sum += signs[pos] * seq[pos];
  }
  if (sum != n) {
    cout << "Impossible\n";
    return 0;
  }
  cout << "Possible\n";
  for (size_t i = 0; i < seq.size(); ++i) {
    if (i) {
      if (signs[i] == +1) {
        cout << " + ";
      } else {
        cout << " - ";
      }
    }
    cout << seq[i];
  }
  cout << " = " << n;
  cout << "\n";
  return 0;

  size_t first_size = signs.size() / 2;
  size_t second_size = signs.size() - first_size;

  unordered_map<int, vi> first_part;
  int iters = 20 * (10 + static_cast<int>(sqrt(n * signs.size())));
  debug(iters);
  for (int it = 0; it < iters; ++it) {
    vi seq;
    int sum = 0;
    for (size_t i = 0; i < first_size; ++i) {
      seq.push_back(1 + (rand() % n));
      if (signs[i] == +1) {
        sum += seq.back();
      } else {
        sum -= seq.back();
      }
    }
    first_part[sum] = seq;
  }
  debug(first_part.size());

  assert(first_size + second_size == signs.size());

  for (int it = 0; it < iters; ++it) {
    vi seq;
    int sum = 0;
    for (size_t i = 0; i < second_size; ++i) {
      seq.push_back(1 + (rand() % n));
      if (signs[first_size + i] == +1) {
        sum += seq.back();
      } else {
        sum -= seq.back();
      }
    }
    int first = n - sum;
    if (first_part.count(first)) {
      cout << "Possible\n";
      const auto seq1 = first_part[first];
      for (size_t i = 0; i < first_size; ++i) {
        if (i) {
          if (signs[i] == +1) {
            cout << " + ";
          } else {
            cout << " - ";
          }
        }
        cout << seq1[i];
      }
      for (size_t i = 0; i < second_size; ++i) {
        if (signs[first_size + i] == +1) {
          cout << " + ";
        } else {
          cout << " - ";
        }
        cout << seq[i];
      }
      cout << " = " << n << "\n";
      return 0;
    }
  }
  cout << "Impossible\n";

  return 0;
}
