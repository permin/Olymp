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
const int INF = std::numeric_limits<int>::max() / 2;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

void solve_test() {
  int days, cakes_per_day;
  cin >> days >> cakes_per_day;
  vii price(days, vi(cakes_per_day, -1));
  for (auto &line : price) {
    for (int &p : line) {
      cin >> p;
    }
    sort(all(line));
  }
  vi dp(days + 1, INF);
  dp[0] = 0;
  for (int days_passed = 1; days_passed <= days; ++days_passed) {
    vi new_dp(days + 1, INF);
    int price_of_cakes_to_buy = 0;
    for (int buy = 0; buy <= cakes_per_day; ++buy) {
      for (int cakes_in_fridge = 0; cakes_in_fridge <= days;
           ++cakes_in_fridge) {
        if (cakes_in_fridge - buy + 1 >= 0 &&
            cakes_in_fridge - buy + 1 <= days) {
          new_dp[cakes_in_fridge] = min(new_dp[cakes_in_fridge],
                                        dp[cakes_in_fridge - buy + 1] +
                                            buy * buy + price_of_cakes_to_buy);
        }
      }
      if (buy != cakes_per_day) {
        price_of_cakes_to_buy += price[days_passed - 1][buy];
      }
    }
    dp = std::move(new_dp);
  }
  cout << *min_element(all(dp));
  cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  for (int test_index = 0; test_index < tests; ++test_index) {
    cout << "Case #" << test_index + 1 << ": ";
    solve_test();
  }
  return 0;
}
