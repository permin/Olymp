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

vector<vector<ll>> dp;

const int MaxN = 11111;
ll cost[MaxN * (MaxN + 1) / 2];
int start[MaxN];

ll get_cost(int a, int b) { return cost[start[b] + a]; }

struct Segment {
  int begin, end;
  bool operator<(const Segment &o) const {
    return make_tuple(begin + end, begin, end) <
           make_tuple(o.begin + o.end, o.begin, o.end);
  }
};

struct Event {
  int x;
  enum Type { Open, Close };
  Type type;
  int id;

  inline bool operator<(const Event &e) const {
    return make_tuple(x, type) < make_tuple(e.x, e.type);
  }
};

enum Status { Closed, NotDiscovered, Inside, Removed };
Event events[MaxN * 2 + 2];
Status statuses[MaxN];

Segment segs[MaxN];
struct BatchProcessedCost {
  void init(int begin, int end) {
    // cerr << "init\n";
    this->begin = begin;
    this->end = end;
    not_opened = end - begin;
    already_closed = 0;

    cost = 0;
    events_num = 0;
    shift = begin;
    for (int i = begin; i < end; ++i) {
      // events.emplace_back();
      events[events_num].x = segs[i].begin;
      events[events_num].type = Event::Open;
      events[events_num].id = i;
      ++events_num;
      events[events_num].x = segs[i].end;
      events[events_num].type = Event::Close;
      events[events_num].id = i;
      ++events_num;
      /*events.back().x = segs[i].end;
      events.back().type = Event::Close;
      events.back().id = i;*/
      // statuses.emplace_back(NotDiscovered);
      statuses[i - shift] = NotDiscovered;
    }
    sort(events, events + events_num);
    for (int i = 0; i < events_num; ++i) {
      if (events[i].type == Event::Open) {
        cost += events[i].x - events[0].x;
      }
    }
    total_points = events_num;
    points_in_left_side = 0;
    position = 0;
    if (events_num != 0) {
      median = events[0].x;
    }
    proceed();
  }

  void proceed() {
    while (points_in_left_side * 2 < total_points) {
      const auto &e = events[position];
      if (statuses[e.id - shift] == Status::Removed) {
        ++position;
        continue;
      }
      cost += 1LL * (e.x - median) * already_closed;
      cost -= 1LL * (e.x - median) * not_opened;

      if (e.type == Event::Close) {
        ++already_closed;
        statuses[e.id - shift] = Status::Closed;
      }
      if (e.type == Event::Open) {
        statuses[e.id - shift] = Status::Inside;
        --not_opened;
      }
      median = e.x;
      ++points_in_left_side;
      ++position;
    }

    // cerr << median << " " << begin << " " << end << "\n";
    debug(begin);
    debug(end);
    debug(median);
    debug(total_points);
    debug(points_in_left_side);
    debug(not_opened);
    debug(already_closed);
    debug(cost);
    debug(statuses);
  }

  void inc() {
    const Segment &s = (segs)[begin];
    int segment_to_remove = begin;
    if (median < s.begin) {
      cost -= s.begin - median;
    }
    if (statuses[segment_to_remove - shift] == Status::NotDiscovered) {
      --not_opened;
    }
    if (median > s.end) {
      cost -= median - s.end;
    }
    if (statuses[segment_to_remove - shift] == Status::Closed) {
      --already_closed;
    }
    if (statuses[segment_to_remove - shift] == Status::Closed) {
      points_in_left_side -= 2;
    }
    if (statuses[segment_to_remove - shift] == Status::Inside) {
      points_in_left_side -= 1;
    }
    statuses[segment_to_remove - shift] = Status::Removed;
    total_points -= 2;
    // cerr << "inc():\n";
    debug(begin);
    debug(end);
    debug(median);
    debug(total_points);
    debug(points_in_left_side);
    debug(not_opened);
    debug(already_closed);
    debug(cost);
    debug(statuses);
    ++begin;
    // assert(begin <= end);
    proceed();
  }

  ll get_cost() {
    debug(cost);
    // assert(cost == st_cost());
    return cost;
  }

  ll st_cost() {
    vector<ll> x;
    for (int i = begin; i < end; ++i) {
      x.push_back((segs)[i].begin);
      x.push_back((segs)[i].end);
    }
    sort(all(x));
    if (x.empty()) {
      return 0;
    }
    int m = x[int(x.size() / 2)];

    ll res = 0;
    for (int i = begin; i < end; ++i) {
      const Segment &s = (segs)[i];
      if (s.end <= m) {
        res += m - s.end;
      }
      if (s.begin >= m) {
        res += s.begin - m;
      }
    }
    return res;
  }

  int shift;
  int begin, end;
  ll cost;
  int not_opened;
  int already_closed;
  int median;
  // vector<Segment> *segs;
  int total_points;
  int points_in_left_side;
  int position;
  // vector<Event> events;
  int events_num;
  set<int> removed_segments;
  // vector<Status> statuses;
};

ll OP;

void solve(int l, int r, int lb, int rb, int groups) {
  if (l >= r) {
    return;
  }
  int m = (l + r) / 2;
  int at = -1;
  {
    /*BatchProcessedCost processor;
    processor.init(segs, lb, m);
    OP += max(1, rb - lb + 1);*/
    for (int j = lb; j <= rb && j < m; ++j) {
      // if (j != lb) {
      // processor.inc();
      //}
      ll cur = dp[groups - 1][j] + get_cost(j, m - 1);
      if (cur < dp[groups][m]) {
        dp[groups][m] = cur;
        at = j;
      }
    }
  }
  solve(l, m, lb, at, groups);
  solve(m + 1, r, at, rb, groups);
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, k;
  cin >> n >> k;
  k = min(k, n);

  dp.assign(k + 1, vector<ll>(n + 1, LLINF / 4));
  for (int g = 0; g <= k; ++g) {
    dp[g][0] = 0;
  }
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> segs[i].begin;
    cin >> segs[i].end;
    if (segs[i].begin > segs[i].end) {
      swap(segs[i].begin, segs[i].end);
    }
    ans += segs[i].end - segs[i].begin;
  }
  sort(segs, segs + n);
  for (int i = 0; i < n; ++i) {
    // cerr << i << " " << segs[i].begin << " " << segs[i].end << "\n";
  }
  if (k == 1) {
    BatchProcessedCost processor;
    processor.init(0, n);
    cout << ans + 2 * processor.get_cost() << "\n";
    return 0;
  }

  if ("n^2 k solution") {
    vector<int> xs;
    for (const auto &s : segs) {
      xs.push_back(s.begin);
      xs.push_back(s.end);
    }
    sort(all(xs));
    xs.erase(unique(all(xs)), xs.end());
    vector<vector<ll>> dp(k + 1, vector<ll>(xs.size() + 1, LLINF));
    dp[0][0] = 0;
    for (int g = 1; g <= k; ++g) {
      for (int p = 0; p <= (int)xs.size(); ++p) {
        if (dp[g - 1][p] == LLINF) {
          continue;
        }
        int first_segment_righter =
            g == 1 ? 0
                   : std::upper_bound(segs, segs + n, p,
                                      [&](const Segment &s, const int point) {
                                        return s.begin + s.end < point * 2;
                                      }) -
                         segs;
        ll cost = -LLINF;
        int first_my = INF;
        for (int cur = g == 1 ? 0 : p + 1; cur <= (int)xs.size(); ++cur) {
          if (cost == -LLINF) {
            cost = 0;
            for (int seg_id = first_segment_righter;; ++seg_id) {
              bool larger = false;
              if (segs[seg_id].begin + segs[seg_id].end > xs[cur] * 2) {
                larger = true;
                if (g != k) {
                  break;
                }
              }
              if (!larger) {
                if (g == 1) {
                  cost += dist(segs[seg_id], xs[cur]);
                } else {
                  if (abs(segs[seg_id].begin + segs[seg_id].end - xs[cur] * 2) <
                      abs(segs[seg_id].begin + segs[seg_id].end - xs[p] * 2)) {
                    first_my = min(first_my, seg_id);
                    cost += dist(segs[seg_id], xs[cur]);
                  } else {
                    cost += dist(segs[seg_id], xs[p]);
                  }
                }
              } else {
                cost += dist(segs[seg_id], xs[cur]);
              }
            }
          } else {
            if (
          }
        }
      }
    }

    return 0;
  }

  int index = 0;

  for (int i = 0; i < n; ++i) {
    start[i] = index;
    BatchProcessedCost processor;
    processor.init(0, i + 1);
    for (int j = max(0, i - n / k - 100); j <= i; ++j) {
      cost[index++] = processor.get_cost();
      if (j != i) {
        processor.inc();
      }
    }
  }

  for (int g = 1; g <= k; ++g) {
    solve(0, n + 1, 0, n - 1, g);
  }
  // ll ans = dp[k][n];
  debug(ans);
  cout << ans + 2 * dp[k][n] << "\n";
  cerr << OP << "\n";

  return 0;
}
