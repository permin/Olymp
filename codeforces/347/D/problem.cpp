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
const int INF = std::numeric_limits<int>::max() / 10000;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

int my_score;

vi players_affected_by_hacks;

int iters;

inline int solve(const vi &prices, int h0, int h1, int h2, size_t i,
                 const vii &time, const vii &can_be_hacked,
                 vector<viii> &cache) {
  if (i == players_affected_by_hacks.size()) {
    if (h1 + h2 + h0 == 0) {
      return 0;
    } else {
      return INF;
    }
  }
  int &res = cache[i][h0][h1][h2];
  if (res >= 0) {
    return res;
  }

  assert(i < players_affected_by_hacks.size());
  size_t pos = players_affected_by_hacks[i];

  res = INF;
  for (int x = 0; x <= can_be_hacked[pos][0] && x <= h0; ++x) {
    int other_score = 0;
    if (!x && time[pos][0] != 0) {
      other_score += prices[0] / 250 * (250 - time[pos][0]);
    }
    for (int y = 0; y <= can_be_hacked[pos][1] && y <= h1; ++y) {
      if (!y && time[pos][1] != 0) {
        other_score += prices[1] / 250 * (250 - time[pos][1]);
      }
      for (int z = 0; z <= can_be_hacked[pos][2] && z <= h2; ++z) {
        ++iters;
        if (!z && time[pos][2] != 0) {
          other_score += prices[2] / 250 * (250 - time[pos][2]);
        }
        int add = 0;
        if (other_score > my_score) {
          add = 1;
        }
        res = min(res, add + solve(prices, h0 - x, h1 - y, h2 - z, i + 1, time,
                                   can_be_hacked, cache));
        if (!z && time[pos][2] != 0) {
          other_score -= prices[2] / 250 * (250 - time[pos][2]);
        }
      }
      if (!y && time[pos][1] != 0) {
        other_score -= prices[1] / 250 * (250 - time[pos][1]);
      }
    }
  }

  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;

  vi score_for_number_of_people_who_solved(n + 1);
  for (int k = 0; k <= n; ++k) {
    if (n < 2 * k && 2 * k <= 2 * n) {
      score_for_number_of_people_who_solved[k] = 500;
    }
    if (n < 4 * k && 4 * k <= 2 * n) {
      score_for_number_of_people_who_solved[k] = 2 * 500;
    }
    if (n < 8 * k && 8 * k <= 2 * n) {
      score_for_number_of_people_who_solved[k] = 3 * 500;
    }
    if (n < 16 * k && 16 * k <= 2 * n) {
      score_for_number_of_people_who_solved[k] = 4 * 500;
    }
    if (n < 32 * k && 32 * k <= 2 * n) {
      score_for_number_of_people_who_solved[k] = 5 * 500;
    }
    if (32 * k <= n) {
      score_for_number_of_people_who_solved[k] = 6 * 500;
      ;
    }
  }

  vii time(n, vi(3, 0));
  vii solved(n, vi(3, 0));
  vii can_be_hacked(n, vi(3, 0));
  vi total_hacks_possible(3, 0);
  vi problem_stat(3);

  for (int i = 0; i < n; ++i) {
    for (int k = 0; k < 3; ++k) {
      cin >> time[i][k];
      if (time[i][k] == 0) {
        continue;
      }
      solved[i][k] = 1;
      ++problem_stat[k];
      if (time[i][k] < 0) {
        can_be_hacked[i][k] = 1;
        total_hacks_possible[k] += 1;
        time[i][k] *= -1;
        players_affected_by_hacks.push_back(i);
      }
    }
  }
  sort(all(players_affected_by_hacks));
  players_affected_by_hacks.erase(unique(all(players_affected_by_hacks)),
                                  players_affected_by_hacks.end());

  debug(players_affected_by_hacks);
  debug(total_hacks_possible);

  const int max_hacks = 90;
  int total_hacks = total_hacks_possible[0] + total_hacks_possible[1] +
                    total_hacks_possible[2];
  debug(total_hacks);
  if (total_hacks >= max_hacks) {
    cout << "1\n";
    return 0;
  }

  set<vi> prices_explored;

  int ans = n;

  for (int h = total_hacks; h >= 0; --h) {
    map<vi, vector<tuple<int, int, int>>> prices_candidates;
    for (int h0 = total_hacks_possible[0]; h0 >= 0; --h0) {
      for (int h1 = total_hacks_possible[1]; h1 >= 0; --h1) {
        int h2 = h - h0 - h1;
        if (h2 < 0 || h2 > total_hacks_possible[2]) {
          continue;
        }
        vi prices(3);
        for (int k = 0; k < 3; ++k) {
          int h_k = h0;
          if (k == 1) h_k = h1;
          if (k == 2) h_k = h2;
          prices[k] =
              score_for_number_of_people_who_solved[problem_stat[k] - h_k];
        }
        if (prices_explored.count(prices)) {
          continue;
        }
        debug(h0);
        debug(h1);
        debug(h2);
        prices_candidates[prices].emplace_back(h0, h1, h2);
      }
    }
    for (const auto &kv : prices_candidates) {
      assert(kv.second.size() == 1);
      my_score = h * 100;
      const auto &prices = kv.first;
      for (int k = 0; k < 3; ++k) {
        if (solved[0][k]) {
          my_score += prices[k] / 250 * (250 - time[0][k]);
        }
      }
      int def = 0;
      for (int i = 1; i < n; ++i) {
        if (binary_search(all(players_affected_by_hacks), i)) {
          continue;
        }
        int other_score = 0;
        if (solved[i][0]) other_score += prices[0] / 250 * (250 - time[i][0]);
        if (solved[i][1]) other_score += prices[1] / 250 * (250 - time[i][1]);
        if (solved[i][2]) other_score += prices[2] / 250 * (250 - time[i][2]);
        if (other_score > my_score) {
          ++def;
        }
      }

      debug(prices);
      debug(def);
      vector<viii> cache(players_affected_by_hacks.size() + 1,
                         viii(total_hacks_possible[0] + 1,
                              vii(total_hacks_possible[1] + 1,
                                  vi(total_hacks_possible[2] + 1, -1))));
      for (const auto &t : kv.second) {
        int h0, h1, h2;
        tie(h0, h1, h2) = t;
        ans = min(ans, 1 + def + solve(prices, h0, h1, h2, 0, time,
                                       can_be_hacked, cache));
        /*if (ans == 1) {
          cout << ans << "\n";
          return 0;
        }*/
      }
    }
    for (const auto &kv : prices_candidates) {
      prices_explored.insert(kv.first);
    }
  }
  debug(prices_explored);
  cout << ans << "\n";

  debug(iters);

  return 0;
}
