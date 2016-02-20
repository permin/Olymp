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

int D;
double prob_of_loss[4][3][3][3];

void go(vector<int> &dealer, vector<int> &player, int mode = 0) {
  {
    vi d = dealer;
    vi p = player;
    sort(d.rbegin(), d.rend());
    sort(p.rbegin(), p.rend());
    int d_l = 0;
    int p_l = 0;
    for (size_t i = 0; i < min(d.size(), p.size()); ++i) {
      if (d[i] > p[i]) {
        p_l += 1;
      } else {
        d_l += 1;
      }
    }
    prob_of_loss[dealer.size()][player.size()][d_l][p_l] +=
        pow(1.0 / D, dealer.size() + player.size());
  }
  if (dealer.size() < 3 && mode == 0) {
    for (int i = 0; i < D; ++i) {
      dealer.push_back(i);
      go(dealer, player, mode);
      dealer.pop_back();
    }
  }
  mode = 1;
  if (player.size() < 2 && mode == 1) {
    for (int i = 0; i < D; ++i) {
      player.push_back(i);
      go(dealer, player, mode);
      player.pop_back();
    }
  }
}

double dp[102][102];

double prob_of_dealer_win(int k, int p) {
  assert(k >= 0 && p >= 0);
  assert(!(k <= 1 && p <= 0));
  if (k == 1)
    return 0.0;
  if (p == 0)
    return 1.0;
  double &res = dp[k][p];
  if (res >= 0) {
    return res;
  }
  res = 0;
  int dealer_dices = (k >= 4 ? 3 : k - 1);
  double opt1 = 0.0;
  double opt2 = 0.0;
  int total_dices = min(dealer_dices, (p > 1) ? 2 : 1);
  for (int d_l = 0; d_l <= total_dices; ++d_l) {
    for (int p_l = 0; p_l <= total_dices; ++p_l) {
      if (prob_of_loss[dealer_dices][1][d_l][p_l] > EPS) {
        opt1 += prob_of_loss[dealer_dices][1][d_l][p_l] *
                prob_of_dealer_win(k - d_l, p - p_l);
      }
      if (p > 1) {
        if (prob_of_loss[dealer_dices][2][d_l][p_l] > EPS) {
          opt2 += prob_of_loss[dealer_dices][2][d_l][p_l] *
                  prob_of_dealer_win(k - d_l, p - p_l);
        }
      } else {
        opt2 = 1.0;
      }
    }
  }
  res = min(opt1, opt2);
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int a = 0; a < 4; ++a) {
      for (int b = 0; b < 3; ++b) {
        for (int c = 0; c < 3; ++c) {
          for (int d = 0; d < 3; ++d) {
            prob_of_loss[a][b][c][d] = 0.0;
          }
        }
      }
    }
    cin >> D;
    for (int a = 0; a < 102; ++a) {
      for (int b = 0; b < 102; ++b) {
        dp[a][b] = -1.0;
      }
    }
    vi a, b;
    go(a, b);

    int x, y;
    cin >> x >> y;
    swap(x, y);
    printf("%0.18lf\n", prob_of_dealer_win(x, y));
  }

  return 0;
}
