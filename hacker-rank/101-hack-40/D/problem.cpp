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

int X;

struct Segment {
  int id = -1;
  int xm, ym, xM, yM;
  long double cur_y() const {
    int dx = xM - xm;
    int shift = X - xm;
    if (shift == 0) {
      return ym;
    }
    assert(dx > 0);
    return ym + ((long double)1.0) * (yM - ym) * shift / dx;
  }

  int out_x() const {
    if (ym < yM) {
      return xm;
    } else {
      return xM;
    }
  }

  bool operator<(const Segment &s) const {
    return make_pair(cur_y(), id) < make_pair(s.cur_y(), s.id);
  }
};

struct Req {
  int x, y;
  int id;
  enum Type { Insert, Seg, Input, Remove };
  Type type;
  bool operator<(const Req &r) const {
    return make_tuple(x, type, id) < make_tuple(r.x, r.type, r.id);
  }
};

int find_out_x(int s, const vector<Segment> &segs, const vi &from_seg_to_seg,
               vi &from_seg_to_ans_closure) {
  int &res = from_seg_to_ans_closure[s];
  if (res != INF) {
    return res;
  }
  if (from_seg_to_seg[s] == -1) {
    return res = segs[s].out_x();
  }
  return res = find_out_x(from_seg_to_seg[s], segs, from_seg_to_seg,
                          from_seg_to_ans_closure);
}

int main() {
  std::ios_base::sync_with_stdio(false);

  vector<Req> requests;
  int n, q;
  cin >> n >> q;
  vector<Segment> segs(n);
  for (int i = 0; i < n; ++i) {
    segs[i].id = i;
    cin >> segs[i].xm >> segs[i].ym >> segs[i].xM >> segs[i].yM;
    if (segs[i].xm > segs[i].xM) {
      swap(segs[i].xm, segs[i].xM);
      swap(segs[i].ym, segs[i].yM);
    }

    requests.emplace_back();
    if (segs[i].ym < segs[i].yM) {
      requests.back().x = segs[i].xm;
      requests.back().y = segs[i].ym;
    } else {
      requests.back().x = segs[i].xM;
      requests.back().y = segs[i].yM;
    }
    requests.back().id = i;
    requests.back().type = Req::Seg;

    requests.emplace_back();
    requests.back().x = segs[i].xm;
    requests.back().y = segs[i].ym;
    requests.back().type = Req::Insert;
    requests.back().id = i;

    requests.emplace_back();
    requests.back().x = segs[i].xM;
    requests.back().y = segs[i].yM;
    requests.back().type = Req::Remove;
    requests.back().id = i;
  }
  for (int i = 0; i < q; ++i) {
    requests.emplace_back();
    cin >> requests.back().x >> requests.back().y;
    requests.back().type = Req::Input;
    requests.back().id = i;
  }
  vector<int> from_input_to_seg(q, -1);
  vector<int> from_seg_to_seg(n, -1);
  sort(all(requests));
  {
    set<Segment> discovered_segments;
    int i = 0;
    while (i < (int)requests.size()) {
      X = requests[i].x;
      /*while (last_remove < X) {
        if (remove_seg.count(last_remove) == 1) {
          debug(discovered_segments.size());
          debug(remove_seg[last_remove]);
          for (int id : remove_seg[last_remove]) {
            discovered_segments.erase(segs[id]);
          }
          debug(discovered_segments.size());
        }
        ++last_remove;
      }*/

      int j = i;
      while (j < (int)requests.size() && requests[j].x == X) {
        if (requests[j].type == Req::Insert) {
          discovered_segments.insert(segs[requests[j].id]);
        } else if (requests[j].type == Req::Remove) {
          discovered_segments.erase(segs[requests[j].id]);
        } else {
          /*cerr << requests[j].x << " " << requests[j].y << " " <<
             requests[j].id
               << " " << requests[j].type << " \n";*/
          int seg_out = -1;
          Segment dummy_req_seg;
          dummy_req_seg.xm = dummy_req_seg.xM = requests[j].x;
          assert(requests[j].x == X);
          dummy_req_seg.ym = dummy_req_seg.yM = requests[j].y;
          dummy_req_seg.id = -2;
          auto it = discovered_segments.lower_bound(dummy_req_seg);

          if (it == discovered_segments.begin()) {
            // cerr << "drop!\n";
          } else {
            --it;
            seg_out = it->id;
          }
          if (requests[j].type == Req::Input) {
            debug(seg_out);
            from_input_to_seg[requests[j].id] = seg_out;
          } else if (requests[j].type == Req::Seg) {
            int input_seg_id = requests[j].id;
            debug(input_seg_id);
            debug(seg_out);
            from_seg_to_seg[input_seg_id] = seg_out;
          }
        }
        ++j;
      }
      i = j;
    }
  }
  vi from_seg_to_ans_closure(n, INF);

  debug(from_input_to_seg);
  debug(from_seg_to_seg);
  vi ans(q);
  for (int i = 0; i < (int)requests.size(); ++i) {
    if (requests[i].type == Req::Input) {
      int id = requests[i].id;
      if (from_input_to_seg[id] == -1) {
        ans[id] = requests[i].x;
      } else {
        ans[id] = find_out_x(from_input_to_seg[id], segs, from_seg_to_seg,
                             from_seg_to_ans_closure);
      }
    }
  }
  for (int x : ans) {
    cout << x << "\n";
  }

  return 0;
}
