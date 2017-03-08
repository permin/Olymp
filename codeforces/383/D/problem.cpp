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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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
ostream &operator<<(ostream &o, const unordered_map<T, V> &v) {
  o << "{";
  O__(o, v);
  o << "}";
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

// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;

typedef std::map<size_t, size_t> Map;  // mask -> max depth

inline size_t charMask(char ch) { return (1 << (ch - 'a')); }

inline bool getValue(Map &maskToMaxDepth, size_t maskToSearch, size_t &depth) {
  auto it = maskToMaxDepth.find(maskToSearch);
  if (it == maskToMaxDepth.end()) {
    return false;
  }
  depth = it->second;
  return true;
}

Map &join(Map &first, Map &second, size_t &maxSum) {
  if (first.size() < second.size()) {
    return join(second, first, maxSum);
  }
  for (const auto &kv : second) {
    const size_t mask = kv.first;
    {
      for (char c = 'a'; c <= 'v'; ++c) {
        size_t maskInFirst = mask ^ charMask(c);
        size_t depth;
        if (getValue(first, maskInFirst, depth)) {
          maxSum = max(maxSum, depth + kv.second);
        }
      }
      {
        size_t maskInFirst = mask;
        size_t depth;
        if (getValue(first, maskInFirst, depth)) {
          maxSum = max(maxSum, depth + kv.second);
        }
      }
    }
  }
  for (const auto &kv : second) {
    const size_t mask = kv.first;
    first[mask] = max(first[mask], kv.second);
  }
  second.clear();
  return first;
}

void dfs(int v, const vector<vector<pair<int, char>>> &children, size_t mask,
         size_t depth, vector<Map> &maskToMaxDepth, vector<size_t> &ans) {
  maskToMaxDepth[v][mask] = depth;
  size_t maxSum = depth + depth;
  for (const auto &v2Char : children[v]) {
    dfs(v2Char.first, children, mask ^ charMask(v2Char.second), depth + 1,
        maskToMaxDepth, ans);
    ans[v] = max(ans[v], ans[v2Char.first]);
    // assert(!maskToMaxDepth[v2Char.first].maskToMaxDepth.empty());
    // debug(v2Char.first);
    // debug(maskToMaxDepth[v2Char.first].maskToMaxDepth);

    maskToMaxDepth[v].swap(
        join(maskToMaxDepth[v], maskToMaxDepth[v2Char.first], maxSum));
  }
  ans[v] = max(ans[v], maxSum - depth - depth);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<vector<pair<int, char>>> children(n);
  for (int i = 0; i + 1 < n; ++i) {
    int x;
    string s;
    cin >> x >> s;
    --x;
    children[x].emplace_back(i + 1, s[0]);
  }
  vector<Map> maskToMaxDepth(n);
  vector<size_t> ans(n);
  dfs(0, children, 0, 0, maskToMaxDepth, ans);
  for (size_t a : ans) {
    cout << a << " ";
  }
  cout << "\n";
  return 0;
}
