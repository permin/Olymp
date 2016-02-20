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

bool can_finish_in_time(const vector<ll> &deadlines,
                        const vi &processing_times) {
  // sort(all(deadlines));
  // sort(all(processing_times));

  assert(is_sorted(all(deadlines)));
  assert(is_sorted(all(processing_times)));

  set<pair<ll, size_t>> expected_finish_times;
  for (int i = 0; i < static_cast<int>(processing_times.size()); ++i) {
    expected_finish_times.emplace(processing_times[i], i);
  }
  for (size_t i = 0; i < deadlines.size(); ++i) {
    pair<ll, size_t> time_proc = *expected_finish_times.begin();
    expected_finish_times.erase(*expected_finish_times.begin());
    if (time_proc.first > deadlines[i]) {
      return false;
    }
    time_proc.first += processing_times[time_proc.second];
    expected_finish_times.insert(time_proc);
  }
  return true;
}

bool can_finish_in_time(int loads_number, const vi &wash_time, int dryers,
                        int dry_time, ll time) {
  vector<ll> deadlines(loads_number);
  vector<ll> t(dryers, time - dry_time);
  int j = 0;
  for (int i = 0; i < loads_number; ++i) {
    deadlines[i] = t[j];
    t[j] -= dry_time;
    ++j;
    if (j == dryers) {
      j = 0;
    }
  }
  reverse(all(deadlines));
  return can_finish_in_time(deadlines, wash_time);
}

ll solve(const vector<ll> &deadlines, const vi &processing_times) {
  // sort(all(deadlines));
  // sort(all(processing_times));

  assert(is_sorted(all(deadlines)));
  assert(is_sorted(all(processing_times)));

  set<pair<ll, size_t>> expected_finish_times;
  for (int i = 0; i < static_cast<int>(processing_times.size()); ++i) {
    expected_finish_times.emplace(processing_times[i], i);
  }
  ll res = 0;
  for (size_t i = 0; i < deadlines.size(); ++i) {
    pair<ll, size_t> time_proc = *expected_finish_times.begin();
    expected_finish_times.erase(*expected_finish_times.begin());
    res = max(res, time_proc.first - deadlines[i]);
    time_proc.first += processing_times[time_proc.second];
    expected_finish_times.insert(time_proc);
  }
  return res;
}

ll solve(int loads_number, const vi &wash_time, int dryers, int dry_time) {
  vector<ll> deadlines(loads_number);
  vector<ll> t(dryers, -dry_time);
  int j = 0;
  for (int i = 0; i < loads_number; ++i) {
    deadlines[i] = t[j];
    t[j] -= dry_time;
    ++j;
    if (j == dryers) {
      j = 0;
    }
  }
  reverse(all(deadlines));
  return solve(deadlines, wash_time);
}

void solve_test2() {
  int loads_number, washing_machines, dryers, dry_time;
  cin >> loads_number >> washing_machines >> dryers >> dry_time;
  vi wash_time(washing_machines);
  for (int &x : wash_time) {
    cin >> x;
  }
  dryers = min(dryers, loads_number);
  sort(all(wash_time));
  cout << solve(loads_number, wash_time, dryers, dry_time);
}

void solve_test() {
  int loads_number, washing_machines, dryers, dry_time;
  cin >> loads_number >> washing_machines >> dryers >> dry_time;
  vi wash_time(washing_machines);
  for (int &x : wash_time) {
    cin >> x;
  }
  dryers = min(dryers, loads_number);
  sort(all(wash_time));
  ll lower = 0 * static_cast<ll>(*max_element(all(wash_time)) + dry_time);
  ll upper =
      loads_number * static_cast<ll>(*max_element(all(wash_time)) + dry_time) +
      1;
  while (lower + 1 < upper) {
    ll time = lower + (upper - lower) / 2;
    if (can_finish_in_time(loads_number, wash_time, dryers, dry_time, time)) {
      upper = time;
    } else {
      lower = time;
    }
  }
  assert(can_finish_in_time(loads_number, wash_time, dryers, dry_time, upper));
  assert(!can_finish_in_time(loads_number, wash_time, dryers, dry_time,
                             upper - 1));

  cout << upper;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t test_number = 0;
  cin >> test_number;
  for (size_t test_index = 0; test_index < test_number; ++test_index) {
    cout << "Case #" << test_index + 1 << ": ";
    solve_test2();
    cout << "\n";
  }
  return 0;
}
