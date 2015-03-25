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

template<class T>
typename set<T>::iterator grLess(const std::set<T>& s, const T& x) {
    auto it = s.lower_bound(x);
    if (it == s.begin())
        return s.end();
    assert(it == s.end() || *it >= x);
    --it;
    assert(*it < x);
    return it;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vi x(n);
    vi w(n);

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> w[i];
    }

    vi p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    sort(all(p), [&](int i, int j) {
        return x[i] - w[i] < x[j] - w[j];
    });

    set<pii> Q;

    vi p2(n);
    for (int i = 0; i < n; ++i) {
        p2[i] = i;
    }
    sort(all(p2), [&](int i, int j) {
            return x[i] + w[i] < x[j] + w[j];
    });

    int j = 0;
    vii prev2(n);
    for (int i: p) {
        while(j < n && x[p2[j]] + w[p2[j]] <= x[i] - w[i]) {
            Q.insert(pii(x[p2[j]], p2[j]));
            ++j;
        }
        auto it = grLess(Q, pii(x[i], i));
        if (it == Q.end()) {
        } else {
            ++it;
            do {
                --it;
                prev2[i].push_back(it->second);
                assert(x[i] > x[prev2[i].back()]);
                assert(i != prev2[i].back());
            } while (prev2[i].size() < 100 && it != Q.begin());
        }
    }

    vi p3(n);
    for (int i = 0; i < n; ++i)
        p3[i] = i;
    sort(all(p3), [&](int i, int j) {
        return x[i] < x[j];
    });
    vi len(n, 1);
    for (int i: p3) {
        for (int v2: prev2[i])
            len[i] = max(len[i], 1 + len[v2]);
    }
    cout << *max_element(all(len)) << "\n";

    return 0;
}
