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

const int kStraight = 0;
const int kMinus = 1;
const int kPlus = 2;

const int kMod = 1000000007;
int add(int x, int y) { return (x + y) % kMod; }
int mul(int x, int y) {
  ll res = 1LL * x * y;
  return (int(res % kMod));
}

struct Node {
  Node(const vii &data) : data(data) { ans.assign(2, vi(2)); }
  vii ans;
  int left;
  int right;
  const vii &data;
};

Node join(const Node &first, const Node &second) {
  Node newNode(first.data);
  newNode.left = first.left;
  newNode.right = second.right;
  for (int takeLeft = 0; takeLeft < 2; ++takeLeft) {
    for (int takeRight = 0; takeRight < 2; ++takeRight) {
      int &r = newNode.ans[takeLeft][takeRight] = 0;
      int L = newNode.left + (1 - takeLeft);
      int R = newNode.right - (1 - takeRight);
      if (L > R) {
        continue;
      }
      r = add(r, mul(first.ans[takeLeft][1], second.ans[1][takeRight]));
      r = add(r, mul(mul(first.ans[takeLeft][0], second.ans[0][takeRight]),
                     mul(newNode.data[first.right][kPlus],
                         newNode.data[second.left][kMinus])));
    }
  }
  return newNode;
}

struct Tree {
  vector<Node> nodes;
  vii data;
  Tree(int n) {
    data.assign(n, vi(3, 0));
    for (int i = 0; i < n; ++i) {
      data[i][kStraight] = 1;
    }
    create(0, n - 1);
  }
  void create(int l, int r) {
    Node newNode(data);
    newNode.left = l;
    newNode.right = r;
    size_t i = nodes.size();
    nodes.push_back(newNode);
    if (l == r) {
      newNode.ans[1][1] = data[l][kStraight];
    } else {
      int m = (l + r) / 2;
      create(l, m);
      create(m, r);
      nodes[i] = join(nodes[i * 2 + 1], nodes[i * 2 + 2]);
    }
  }
}

void SolveTest() {
  cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests = 0;
  cin >> tests;
  for (int testIndex = 0; testIndex < tests; ++testIndex) {
    cout << "Case #" << testIndex + 1 << ": ";
    cerr << "Case #" << testIndex + 1 << ": ...\n";
    SolveTest();
  }
  return 0;
}
