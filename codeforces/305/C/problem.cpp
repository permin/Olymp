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

template <class T, class V>
ostream& operator << (ostream& o, const unordered_map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}
template <class T>
ostream& operator << (ostream& o, const multiset<T>& v) {o << "{";O__(o, v);o << "}";return o;}

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

const int N = 500*1000 +4;

size_t greaterThan(const std::set<size_t>& s, size_t v) {
    return std::distance(s.upper_bound(v), s.end());
}

size_t lessThan(const std::set<size_t>& s, size_t v) {
    auto it = s.lower_bound(v);
    size_t d = distance(s.begin(), it);
    if (d != s.size() && *it == v) {
        d -= 1;
    }
    return d;
}

std::vector<size_t> rec;
template<class It, class F>
void doit(It b, It e, F f) {
    if (b == e) {
        if (!rec.empty())
            f(rec);
        return;
    }
    doit(b + 1, e, f);
    rec.push_back(*b);
    doit(b + 1, e, f);
    rec.pop_back();
}

namespace std{
template<>
struct hash<std::vector<size_t>> {
    size_t operator()(const std::vector<size_t>& b) const {
        size_t r = 0;
        for (size_t x: b) {
            r *= 239 * 239 * 239;
            r += x;
        }
        return r;
    }
};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::map<size_t, size_t> p;
    int n;
    cin >> n;
    int q ;
    cin >> q;
    vector<size_t> a(n);
    vector<vector<size_t>> al(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        size_t m = a[i];
        for (size_t x = 2; x * x <= m; ++x) {
            if (m % x == 0) {
                while(m % x == 0) m /= x;
                if (p.count(x) == 0) {
                    size_t id = p.size();
                    p[x] = id;
                }
                al[i].push_back(p[x]);
            }
        }
        if (m != 1) {
            size_t x = m;
            if (p.count(x) == 0) {
                size_t id = p.size();
                p[x] = id;
            }
            al[i].push_back(p[x]);
        }
    }
    debug(p);
    debug(al);
    std::unordered_map<std::vector<size_t>, int> stat;
    vector<bool> is(n);
    long long res = 0;
    ll num = 0;

    multiset<size_t> val;

    while(q-->0) {
        debug(stat);
        int x;
        cin >> x;
        --x;
        debug(al[x]);

        if (is[x]) {
            val.erase(val.find(a[x]));
            --num;
            is[x] = 0;
            doit(all(al[x]), [&](const std::vector<size_t>& b) {
                    stat[b] -= 1;
            });
            ll add = 0;
            doit(all(al[x]), [&](const std::vector<size_t>& b) {
                add += ((b.size() & 1)? +1: -1) * stat[b];
            });
            debug(add);
            res -= add;
        } else {
            ll add = 0;
            doit(all(al[x]), [&](const std::vector<size_t>& b) {
                add += ((b.size() & 1)? +1: -1) * stat[b];
            });
            debug(add);

            val.insert(a[x]);
            ++num;
            res += add;
            is[x] = 1;
            doit(all(al[x]), [&](const std::vector<size_t>& b) {
                    stat[b] += 1;
            });
        }
        cout << (num) * (num - 1) / 2 - res << "\n";
        debug(val);

//        int cr = 0;
//        {
//            for (auto it = val.begin(); it != val.end(); ++it) {
//                for (auto it2 = std::next(it); it2 != val.end(); ++it2) {
//                if (__gcd(*it,*it2) == 1) {
//                    ++cr;
//                }
//            }
//            }
//        }
//
//        assert(cr == ((num) * (num - 1) / 2 - res ));
    }
    return 0;
}
