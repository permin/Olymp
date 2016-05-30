#include "majority-1.h"

#include <message.h>
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

  size_t n = MyNodeId();

  vi votes;
  for (long long pos = MyNodeId(); pos < GetN(); pos += NumberOfNodes()) {
    votes.push_back(GetVote(pos));
  }
  int cand = 0;
  int num = 0;
  for (int x : votes) {
    if (num == 0) {
      cand = x;
      num = 1;
    } else {
      if (cand == x) {
        ++num;
      } else {
        --num;
      }
    }
  }
  num = count(all(votes), cand);

  if (MyNodeId() > 0) {
    Receive(MyNodeId() - 1);
    int prev_cand = GetInt(MyNodeId() - 1);
    int prev_num = GetInt(MyNodeId() - 1);
    if (prev_cand == cand) {
      num += prev_num;
    } else {
      if (num > prev_num) {
        num -= prev_num;
      } else {
        num = prev_num - num;
        cand = prev_cand;
      }
    }
  }
  if (MyNodeId() < NumberOfNodes() - 1) {
    PutInt(MyNodeId() + 1, cand);
    PutInt(MyNodeId() + 1, num);
    Send(MyNodeId() + 1);

    Receive(NumberOfNodes() - 1);
    cand = GetInt(NumberOfNodes() - 1);

    PutInt(NumberOfNodes() - 1, count(all(votes), cand));
    Send(NumberOfNodes() - 1);

  } else {
    for (int i = 0; i < NumberOfNodes() - 1; ++i) {
      PutInt(i, cand);
      Send(i);
    }
    num = count(all(votes), cand);
    for (int i = 0; i < NumberOfNodes() - 1; ++i) {
      Receive(i);
      num += GetInt(i);
    }

    cout << "Num=" << (num) << "\n";
    if (num + num > GetN()) {
      cout << cand;
    } else {
      cout << "NO WINNER";
    }
  }

  // HELLO
  return 0;
}
