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
    if (!f)
      o << ", ";
    if (IsIterable__<decltype(x)>::value)
      o << "\n";
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

bool can_be_extended_to_contest(vi contest_problems) {
  if (contest_problems.empty()) {
    return true;
  }
  if (!is_sorted(all(contest_problems))) {
    return false;
  }
  if (std::unique(all(contest_problems)) != contest_problems.end()) {
    return false;
  }
  int last = contest_problems[0];
  int additional = 0;
  for (int i = 1; i < static_cast<int>(contest_problems.size()); ++i) {
    if (contest_problems[i] <= last + 10) {
      last = contest_problems[i];
    } else {
      last += 10;
      ++additional;
      --i;
    }
    if (additional + contest_problems.size() > 4) {
      break;
    }
  }
  return (additional + contest_problems.size() <= 4);
}

int solve(const vi &a) {
  int n = static_cast<int>(a.size());
  vi dp(n + 1, 3 * n);
  dp[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    vi contest_problems;
    for (int j = 0; i + j < n && j < 4; ++j) {
      contest_problems.push_back(a[i + j]);
      if (can_be_extended_to_contest(contest_problems)) {
        dp[i] = min(dp[i], dp[i + j + 1] + (3 - j));
      }
    }
  }
  return dp[0];
}

int solve_greedy(const vi &a) {
  int n = static_cast<int>(a.size());
  int additional = 0;
  int last = a[0];
  int current_contest_length = 1;
  for (int i = 1; i < n; ++i) {
    if (current_contest_length == 4) {
      current_contest_length = 1;
      last = a[i];
    } else {
      if (last >= a[i]) {
        ++current_contest_length;
        ++additional;
        --i;
      } else if (last + 10 < a[i]) {
        last += 10;
        ++additional;
        ++current_contest_length;
        --i;
      } else {
        last = a[i];
        ++current_contest_length;
      }
    }
  }
  if (current_contest_length < 4) {
    additional += (4 - current_contest_length);
  }
  return additional;
}

vi gen_random(int n, int m) {
  vi res(n);
  for (int i = 0; i < n; ++i) {
    res[i] = rand() % m;
    ++res[i];
  }
  return res;
}

void ss() {
  for (int t = 0; t < 1000 * 1000; ++t) {
    int n = rand() % 40;
    n += 1;
    vi a = gen_random(n, 5);
    int solve_ans = solve(a);
    int solve_greedy_and = solve_greedy(a);
    if (solve_ans != solve_greedy_and) {
      debug(solve_ans);
      debug(solve_greedy_and);
      debug(a);
    }
  }
  debug("done!");
}

void solve_test() {
  int n;
  cin >> n;
  vi a(n);
  for (int &x : a) {
    cin >> x;
  }
  assert(solve(a) == solve_greedy(a));
  cout << solve(a);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  if (0) {
    ss();
    return 0;
  }
  size_t test_number = 0;
  cin >> test_number;
  for (size_t test_index = 0; test_index < test_number; ++test_index) {
    cout << "Case #" << test_index + 1 << ": ";
    solve_test();
    cout << "\n";
  }
  return 0;
}
