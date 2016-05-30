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

struct T {
  vector<int> data;
  vector<int> t;
};

void upd(int i, vi &data, int add) {
  for (; i < static_cast<int>(data.size()); i = i | (i + 1)) {
    data[i] += add;
  }
}

int sum(vi &data, int till) {
  int res = 0;
  int i = till;
  for (; i >= 0; i = (i & (i + 1)) - 1) {
    res += data[i];
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> t(n);
  vector<int> x(n);

  vector<int> uniq_numbers;

  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> t[i] >> x[i];
  }
  uniq_numbers = x;
  sort(all(uniq_numbers));
  uniq_numbers.erase(unique(all(uniq_numbers)), uniq_numbers.end());

  vector<T> ts(uniq_numbers.size());
  for (int i = 0; i < n; ++i) {
    int j = int(lower_bound(all(uniq_numbers), x[i]) - uniq_numbers.begin());
    ts[j].t.push_back(t[i]);
  }
  for (size_t i = 0; i < ts.size(); ++i) {
    auto &ar = ts[i].t;
    sort(all(ar));
    ar.erase(unique(all(ar)), ar.end());
    ts[i].data.assign(ts[i].t.size(), 0);
  }

  for (int i = 0; i < n; ++i) {
    int number_id =
        int(lower_bound(all(uniq_numbers), x[i]) - uniq_numbers.begin());
    int time_id =
        int(lower_bound(all(ts[number_id].t), t[i]) - ts[number_id].t.begin());
    if (a[i] == 1) {
      upd(time_id, ts[number_id].data, +1);
    } else if (a[i] == 2) {
      upd(time_id, ts[number_id].data, -1);
    } else {
      cout << sum(ts[number_id].data, time_id) << "\n";
    }
  }

  return 0;
}
