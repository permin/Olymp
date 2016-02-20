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

int bit_count[1 << 16];

bool has_bit(int mask, int k) { return (mask & (1 << k)); }

int log2(int n) {
  int k = 0;
  while ((1 << k) < n) {
    ++k;
  }
  return k;
}

int calc_is_possible_to_win(int players_set, int player, int wins, const vii &w,
                            viii &cache) {
  assert(has_bit(players_set, player));

  int &res = cache[players_set][player][wins];
  if (res >= 0) {
    return res;
  }
  res = 0;
  const int players_set_size = bit_count[players_set];
  if (players_set_size == 1) {
    return (res = (wins == 0));
  }
  int maximum_wins = log2(players_set_size);
  for (int subset = players_set; subset != 0;
       subset = (subset - 1) & players_set) {
    if (bit_count[subset] != players_set_size / 2 || !has_bit(subset, player)) {
      continue;
    }
    if (wins < maximum_wins - 1 &&
        calc_is_possible_to_win(subset, player, wins, w, cache)) {
      return (res = 1);
    }
    if (wins >= maximum_wins - 1) {
      int lose_this_round = maximum_wins - wins;
      if (calc_is_possible_to_win(subset, player, maximum_wins - 1, w, cache)) {
        for (int i = 0; i < static_cast<int>(w.size()); ++i) {
          if (has_bit(players_set ^ subset, i) &&
              w[player][i] != lose_this_round &&
              calc_is_possible_to_win(players_set ^ subset, i, maximum_wins - 1,
                                      w, cache)) {
            return (res = 1);
          }
        }
      }
    }
  }
  return res;
}

vector<pii> solve(int n, const vii &w) {
  int k = log2(n);
  vi wins_to_place(k + 1, 1);
  for (int i = 0; i <= k; ++i) {
    if (i == 0) {
      wins_to_place[k - i] = 1;
    } else {
      wins_to_place[k - i] = 1 << (i - 1);
      wins_to_place[k - i] += 1;
    }
  }

  viii is_possible_to_win(1 << n, vii(n, vi(k + 1, -1)));

  vector<pii> res;
  for (int i = 0; i < n; ++i) {
    int m = INF;
    int M = 0;
    for (int j = 0; j <= k; ++j) {
      if (calc_is_possible_to_win((1 << n) - 1, i, j, w, is_possible_to_win)) {
        m = min(m, j);
        M = max(M, j);
      }
    }
    res.emplace_back(wins_to_place[M], wins_to_place[m]);
  }
  return res;
}
vi simulate_game(int n, const vii &w, vi order) {
  queue<int> q;
  for (int o : order) {
    q.push(o);
  }
  vi wins(n, 0);
  while (q.size() > 1) {
    int x = q.front();
    q.pop();
    int y = q.front();
    q.pop();
    int winner = y;
    if (w[x][y]) {
      winner = x;
    }
    q.push(winner);
    wins[winner] += 1;
  }
  return wins;
}

vector<pii> solve_dummy(int n, const vii &w) {
  vi perm;
  for (int i = 0; i < n; ++i) {
    perm.push_back(i);
  }
  vector<pii> res(n, pii(INF, 0));
  do {
    vi wins = simulate_game(n, w, perm);
    for (int i = 0; i < n; ++i) {
      int place = 1 + static_cast<int>(std::count_if(
                          all(wins), [&](int x) { return x > wins[i]; }));
      res[i].first = min(res[i].first, place);
      res[i].second = max(res[i].second, place);
    }
  } while (std::next_permutation(all(perm)));

  return res;
}

vii gen(int n) {
  vii w(n, vi(n, 0));
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
      (rand() % 2 ? w[i][j] : w[j][i]) = 1;
    }
  return w;
}

void ss() {

  for (int i = 0; i < 10 * 1000; ++i) {
    debug(i);
    int k = rand() % 4;
    int n = 1 << k;
    vii w = gen(n);
    auto my_solve_ans = solve(n, w);
    auto dymmy_solve_ans = solve_dummy(n, w);
    if (my_solve_ans != dymmy_solve_ans) {
      debug(w);
      debug(my_solve_ans);
      debug(dymmy_solve_ans);
    }
  }
  debug("done!");
}

void solve_test() {
  int n;
  cin >> n;
  vii w(n, vi(n, -1));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> w[i][j];

  auto places = solve(n, w);
  if (n <= 8) {
    auto dummy_places = solve_dummy(n, w);
    if (dummy_places != places) {
      debug(n);
      debug(w);
      debug(dummy_places);
      debug(places);
    }
  }
  for (const auto &x : places) {
    cout << x.first << " " << x.second << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  for (int mask = 0; mask < (1 << 16); ++mask) {
    bit_count[mask] = __builtin_popcount(mask);
  }
  if (0) {
    ss();
    return 0;
  }
  if (0) {
    for (int i = 0; i < 250; ++i) {
      int n = 16;
      auto w = gen(n);
      auto places = solve(n, w);
      debug(w[1]);
      debug(places[1]);
    }
    return 0;
  }
  size_t test_number = 0;
  cin >> test_number;
  for (size_t test_index = 0; test_index < test_number; ++test_index) {
    debug(test_index);
    cout << "Case #" << test_index + 1 << ":\n";
    solve_test();
  }
  return 0;
}
