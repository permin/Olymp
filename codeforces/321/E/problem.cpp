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

int f2( int n) {
    int r = 1;
    while(r < n)
        r <<= 1;
    return r;
}
int add(int x, int y, int mod) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int sub(int x, int y, int mod) {
    if (y == 0)
        return x;
    return add(x, mod - y, mod);
}

int mul(int x, int y, int mod ) {
    return int((1LL * x * y) % mod);
}

int modpow(int x, int n, int mod) {
    if (n == 0)
        return 1;
    if (n & 1) {
        return mul(x, modpow(x, n - 1, mod), mod);
    } else {
        return modpow(mul(x,x, mod), n/2, mod);
    }
}

class HashIntervalTree {
public:
    HashIntervalTree(int mod, int z, int n2):
        mod(mod),
        z(z),
        n(f2(n2)) {
        delayedUpdate.resize(n + n);
        hash.resize(n + n);
        for (int i = 0; i < n + n; ++i) {
            if (i == 0) {
                powers.push_back(1);
            } else {
                powers.push_back(mul(powers.back(), z, mod));
            }
        }
        iz = modpow(sub(1, z, mod), mod - 2, mod);
    }

    void upd(int l, int r, int val) {
        upd(l, r, 0, n, val, 1);
    }

    void upd(int l, int r, int tl, int tr, int val, int id) {
        if (r <= tl)
            return;
        if (l >= tr)
            return;

        push(tl, tr, id);
        if (l <= tl && tr <= r) {
            setup(tl, tr, val, id);
            return;
        }

        int tm = (tl+tr)/2;
        upd(l,r,tl, tm, val, id << 1);
        upd(l,r,tm, tr, val, (id << 1)+1);
        recalc(id);

        if (tl + 1 < tr) {
            recalc(id);
        }
    }

    int h(int l, int r) {
        return mul(powers[n - 1- l], h(l, r, 0, n, 1), mod);
    }

    int h(int l, int r, int tl, int tr, int id) {
        if (r <= tl)
            return 0;
        if (l >= tr)
            return 0;

        push(tl, tr, id);
        if (l <= tl && tr <= r) {
            return hash[id];
        }
        int tm = (tl + tr) / 2;
        int ans = add(
                h(l, r, tl, tm, id << 1),
                h(l, r, tm, tr, 1+(id << 1)),
                mod);
        recalc(id);
        return ans;
    }

private:

    void recalc(int id) {
        hash[id] = add(hash[id << 1], hash[(id<<1) + 1], mod);
    }
    void push(int tl, int tr, int id) {
        if (delayedUpdate[id] == 0)
            return;
        if (tl + 1 < tr) {
            int tm = (tl+tr)/2;
            setup(tl, tm, delayedUpdate[id], id + id);
            setup(tm, tr, delayedUpdate[id], id + id + 1);
            recalc(id);
        }
        delayedUpdate[id] = 0;
    }
    void setup(int tl, int tr, int val, int id) {
        delayedUpdate[id] = val;
        int s =
                mul(powers[tl],
                    mul(sub(1, powers[tr - tl - 1], mod), iz, mod),
                    mod);
        if (tl + 1 == tr) {
            s = powers[tl];
        }
        hash[id] =
            mul(s,
            val, mod);
    }


    int mod;
    int z;
    int iz;
    vi delayedUpdate;
    vi hash;
    int n;
    vector<int> powers;
};

class D {
public:
    explicit D(int n):
        s(n, '?') {};
    void upd(int l, int r, int v) {
        for (int i = l; i < r; ++i) {
            s[i] = char('0' + v - 1)
                                     ;
        }
    }
    string h(int l, int r) {
        return s.substr(l, r - l);
    }

    string s;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;

    debug(n);
    HashIntervalTree tree(1000 * 1000 * 1000 + 7, 10, n);
    HashIntervalTree tree2(1000 * 1000 * 1000 + 9, 10, n);
    D dummy(n);
    string s;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        tree.upd(i, i + 1, s[i] - '0' + 1);
        tree2.upd(i, i + 1, s[i] - '0' + 1);
        dummy.upd(i, i + 1, s[i] - '0' + 1);
    }
    int q = m+k;
    while(q-->0) {

        debug(dummy.s);
        int x;
        int l,r;
        cin >> x >> l >> r;
        --l;
        if (x == 1) {
            int c;
            cin >> c;
            ++c;
            tree.upd(l, r, c);
            tree2.upd(l, r, c);
            dummy.upd(l, r, c);
        } else {
            int d;
            cin >> d;

            debug(l);
            debug(r);
            debug(d);

            if (tree.h(l, r-d) == tree.h(l+d,r) && tree2.h(l, r-d) == tree2.h(l+d,r) ) {
                debug(tree.h(l, r-d));
                debug(tree.h(l+d, r));
                debug(dummy.h(l, r-d));
                debug(dummy.h(l+d, r));
                cout << "YES\n";
                assert(dummy.h(l,r-d) == dummy.h(l+d, r));
            } else {
                debug(tree2.h(l, r-d));
                debug(tree2.h(l+d, r));
                debug(tree.h(l, r-d));
                debug(tree.h(l+d, r));
                debug(dummy.h(l, r-d));
                debug(dummy.h(l+d, r));
                cout << "NO\n";
                assert(dummy.h(l,r-d) != dummy.h(l+d, r));
            }
        }

    }


    return 0;
}
