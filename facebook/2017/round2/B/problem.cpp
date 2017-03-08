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

void gen(vi &x, ll a, ll b, ll c) {
  for (size_t i = 1; i < x.size(); ++i) {
    x[i] = int((a * x[i - 1] + b) % c) + 1;
  }
}
struct Segment;
ostream &operator<<(ostream &o, const Segment &s);
struct Segment {
  Segment(int firstX, int firstY, int secondX, int secondY)
      : firstX(firstX), firstY(firstY), secondX(secondX), secondY(secondY) {}
  ll doubledAreaUnder() const {
    return static_cast<ll>(secondY + firstY) *
           static_cast<ll>(secondX - firstX);
  }
  bool empty() const { return firstX == secondX; }
  int slope() const {
    if (secondY == firstY) return 0;
    if (firstY < secondY) return +1;
    // assert(firstY > secondY);
    return -1;
  }

  bool operator<(const Segment &other) const { return firstX < other.firstX; }
  pair<Segment, Segment> subdivide(int x) {
    // assert(!empty());
    debug(x);
    debug(*this);
    ll pr = 1LL * (secondY - firstY) * (x - firstX);
    // assert(pr % (secondX - firstX) == 0);
    int y = firstY + int(pr / (secondX - firstX));
    Segment A(firstX, firstY, x, y);
    Segment B(x, y, secondX, secondY);
    return make_pair(A, B);
  }

  int firstX, firstY, secondX, secondY;
};
ostream &operator<<(ostream &o, const Segment &s) {
  o << "{(" << s.firstX << ", " << s.firstY << ") - (" << s.secondX << ", "
    << s.secondY << ")}";
  return o;
}

Segment join(const Segment &left, const Segment &right) {
  // assert(left.firstX < right.secondX);
  // assert(left.secondX == right.firstX);
  // assert(left.slope() == right.slope());
  auto res = Segment(left.firstX, left.firstY, right.secondX, right.secondY);
  // assert(left.slope() == res.slope());
  return res;
}

pair<bool, int> cross(const Segment &a, const Segment &b) {
  debug(a);
  debug(b);
  // assert(a.firstX == b.firstX);
  // assert(a.secondX == b.secondX);
  int d1 = a.firstY - b.firstY;
  int d2 = a.secondY - b.secondY;
  if (1LL * d1 * d2 < 0) {
    ll num = 1LL * (a.firstY - b.firstY) * (a.secondX - a.firstX);
    ll den = a.secondY - a.firstY - b.secondY + b.firstY;
    // assert(num % den == 0);
    int x = int(num / den);
    return make_pair(true, a.firstX - x);
  }
  return make_pair(false, -1);
}
bool higher(const Segment &a, const Segment &b) {
  // assert(a.firstX == b.firstX);
  // assert(a.secondX == b.secondX);
  int d1 = a.firstY - b.firstY;
  int d2 = a.secondY - b.secondY;
  return d1 >= 0 && d2 >= 0;
}

// returns x

struct Partition {
  typedef set<Segment> Set;
  Set segments;
  ll doubledArea = 0;
  map<int, Set::iterator> nextSegment;
  map<int, Set::iterator> previousSegment;
  Partition(int from, int to) { addSegment(Segment(from, 0, to, 0)); }
  void addSegment(const Segment &s) {
    // assert(!s.empty());
    auto it = segments.insert(s);
    doubledArea += s.doubledAreaUnder();
    nextSegment[s.firstX] = it.first;
    previousSegment[s.secondX] = it.first;
  }
  void removeSegment(const Segment &s) {
    segments.erase(s);
    doubledArea -= s.doubledAreaUnder();
    nextSegment.erase(s.firstX);
    previousSegment.erase(s.secondX);
  }
  void addLeft(Segment s) {
    int startX = s.secondX;
    while (!s.empty()) {
      pr();
      debug(s);
      subdivide(s.secondX);
      int maxX = max(s.firstX, previousSegment.at(s.secondX)->firstX);
      subdivide(maxX);
      auto parts = s.subdivide(maxX);

      auto inSet = *nextSegment.at(maxX);
      if (higher(inSet, parts.second)) {
        break;
      }
      if (higher(parts.second, inSet)) {
        removeSegment(inSet);
        addSegment(parts.second);
      } else {
        auto cr = cross(inSet, parts.second);
        // assert(cr.first);
        subdivide(cr.second);
        continue;
      }
      s = parts.first;
    }
    while (previousSegment.count(startX) == 1) {
      auto seg = *previousSegment.at(startX);
      if (previousSegment.count(seg.firstX) == 0) {
        break;
      }
      auto prevSeg = *previousSegment.at(seg.firstX);
      if (seg.slope() == prevSeg.slope()) {
        removeSegment(seg);
        removeSegment(prevSeg);
        addSegment(join(prevSeg, seg));
      } else {
        break;
      }
    }
  }
  void addRight(Segment s) {
    int startX = s.firstX;
    while (!s.empty()) {
      pr();
      debug(s);
      subdivide(s.firstX);
      int minX = min(s.secondX, nextSegment.at(s.firstX)->secondX);
      subdivide(minX);
      auto parts = s.subdivide(minX);

      auto inSet = *previousSegment.at(minX);
      debug(inSet);
      if (higher(inSet, parts.first)) {
        break;
      }
      if (higher(parts.first, inSet)) {
        removeSegment(inSet);
        addSegment(parts.first);
      } else {
        auto cr = cross(inSet, parts.first);
        // assert(cr.first);
        subdivide(cr.second);
        continue;
      }
      s = parts.second;
    }
    while (nextSegment.count(startX) == 1) {
      auto seg = *nextSegment.at(startX);
      if (nextSegment.count(seg.secondX) == 0) {
        break;
      }
      auto nextSeg = *nextSegment.at(seg.secondX);
      if (seg.slope() == nextSeg.slope()) {
        removeSegment(seg);
        removeSegment(nextSeg);
        addSegment(join(seg, nextSeg));
      } else {
        break;
      }
    }
  }

  void subdivide(int x) {
    if (previousSegment.count(x) == 1) {
      return;
    }
    {
      auto it = previousSegment.lower_bound(x);
      // assert(it != previousSegment.end());
      // assert(it->first > x);
      Segment seg = *previousSegment.at(it->first);
      removeSegment(seg);
      auto parts = seg.subdivide(x);
      addSegment(parts.first);
      addSegment(parts.second);
    }
  }
  void pr() { debug(segments); }
};

void SolveTest() {
  int n;
  cin >> n;
  vi x(n);
  cin >> x[0];
  int ax, bx, cx;
  cin >> ax >> bx >> cx;
  vi h(n);
  int ah, bh, ch;
  cin >> h[0];
  cin >> ah >> bh >> ch;
  gen(x, ax, bx, cx);
  gen(h, ah, bh, ch);
  debug(x);
  debug(h);
  for (int &a : x) {
    a *= 2;
  }
  for (int &a : h) {
    a *= 2;
  }
  int first = -*max_element(all(h)) - 100;
  int last = *max_element(all(x)) + *max_element(all(h)) + 100;
  debug(x);
  debug(h);
  Partition partition(first, last);
  double sum = 0;
  for (int i = 0; i < n; ++i) {
    partition.addLeft(Segment(x[i] - h[i], 0, x[i], h[i]));
    partition.addRight(Segment(x[i], h[i], x[i] + h[i], 0));
    sum += static_cast<double>(partition.doubledArea);
  }
  printf("%0.18lf\n", 1.0 * static_cast<double>(sum) / 8);
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  int tests = 0;
  cin >> tests;
  for (int testIndex = 0; testIndex < tests; ++testIndex) {
    cout << "Case #" << testIndex + 1 << ": ";
    cerr << "Case #" << testIndex + 1 << ": ...\n";
    SolveTest();
    cerr << "EAT: " << 1.0 * clock() / (1 + testIndex) * tests / CLOCKS_PER_SEC
         << " sec.\n";
  }
  return 0;
}
