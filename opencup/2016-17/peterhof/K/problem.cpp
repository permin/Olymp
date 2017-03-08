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
  int k;
  cin >> k;
  const int kAlpha = 26;
  vector<int> occ(kAlpha);
  vector<size_t> len(kAlpha);
  vector<string> str(kAlpha);
  while (k-- > 0) {
    string s;
    cin >> s;
    for (char ch : s) {
      int next = ch - 'a';
      for (int letter = 0; letter < kAlpha; ++letter) {
        if (letter == next) {
          if (occ[letter] == 0) {
            str[letter] = string(1, ch);
          } else {
            str[letter].resize(len[letter]);
          }
          len[letter] = 1;
          ++occ[letter];
        } else {
          if (occ[letter] == 0) {
          } else if (occ[letter] == 1) {
            str[letter] += ch;
            ++len[letter];
          } else {
            if (str[letter].size() > len[letter] &&
                str[letter][len[letter]] == ch) {
              ++len[letter];
            } else {
              /*if (letter == 2) {
                debug(str[letter]);
                debug(len[letter]);
              }*/
              str[letter].resize(len[letter]);
            }
          }
        }
      }
    }
    int max_occ = -1;
    int at = -1;
    for (int i = 0; i < kAlpha; ++i) {
      if (occ[i] >= max_occ) {
        max_occ = occ[i];
        at = i;
      }
    }
    cout << str[at].substr(0, len[at]) << endl;
  }

  return 0;
}
