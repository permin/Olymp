#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;};

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {o << "[";O__(o, v);o << "]";return o;}

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

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
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

//using std::rel_ops::operator!=;

struct Time {
    Time():
        h(0),m(0),s(0) {}

    void read() {
        cin >> h >> m >> s;
    }

    ll h, m, s;
};

const ll million = 1000 * 1000;
const ll Total = 12LL * million * million;

ll f(const Time& t) {
    return t.h * million * million +
        t.m * million + t.s;
}

bool operator<(const Time& a, const Time& b) {
    return f(a) < f(b);
}

bool operator==(const Time& a, const Time& b) {
    return f(a) == f(b);
}
bool operator!=(const Time& a, const Time& b) {
    return f(a) != f(b);
}

ll dist(const Time& from, const Time& to) {
    if (from < to) {
        return f(to) - f(from);
    }
    if (to < from) {
        return Total - dist(to, from);
    }
    return 0;
}

int main() {
    //debug(12LL * million * million * 1000*100);
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<Time> t(n);
    for (int i =0 ;i < n;++i)
        t[i].read();
    sort(all(t));

    ll cur = 0;
    for (int i = 1; i < n; ++i) {
        cur += dist(t[i], t[0]);
    }

    ll best = cur;

    for (int i = 1; i < n; ++i) {
        if (t[i - 1] != t[i]) {
            int j = i;
            while(j < n && t[i] == t[j])
                ++j;
            cur += 1LL * n * dist(t[i - 1], t[i]) - Total * ll(j - i);
            best = min(best, cur);
        }
    }

    ll H,M,S;
    S = best % million;
    best /= million;

    M = best % million;
    best /= million;

    H = best;

    cout << H << " " << M << " " << S << "\n";

    return 0;
}
