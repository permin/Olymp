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
bool f = 1; for(const auto& x: c) {if (!f) o << ""; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

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

const size_t mod = size_t(1) << 32;

vi conv(size_t n){
    vi c;
    for (int i = 0; i < 32; ++i) {
        c.push_back(n&1);
        n/=2;
    }
    return c;
}

size_t conv(const vi& c) {
    size_t res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (size_t(1) << i) * c[i];
    }
    return res;
}

vi restoreXor(const vi& z, int shift) {
    vi x(32, -1);
    int j = 0;
    for (int i = 31; i >= 0; --i) {
        if (j < shift) {
            x[i] = z[i];
        } else {
            x[i] = z[i] ^ x[i + shift];
        }
        ++j;
    }
    cerr << conv(x) << " ";
    debug(x);
    {
        size_t v = conv(x);
        assert(conv(z) == ((v ^ (v >> shift)) % mod));
    }

    return x;
}

vi restoreSum(const vi& z, int shift) {
    vi x(32, -1);
    int r = 0;
    for (int i = 0; i < 32; ++i) {
        if (i < shift) {
            x[i] = z[i];
        } else {
            for (int g = 0; g < 2; ++g) {
                if (z[i] == ((g + x[i - shift] + r)%2)) {
                    x[i] = g;
                    r = (g + x[i - shift] + r) / 2;
                    break;
                }
            }
        }
    }
    cerr << conv(x) << " ";
    debug(x);
    {
        size_t v = conv(x);
        assert(conv(z) == ((v + (v << shift)) % mod));
    }
    return x;
}

int main3() {
    for (int i = 0; i < 1000; ++i) {
        size_t x = rand() % mod;
        assert(x == conv(conv(x)));
    }
    while(1) {
        size_t n;
        cin >> n;
        size_t h = n;
        cerr << h << " ";debug(conv(h));
        h = (h + (h<<10)) % mod;
        cerr << h << " ";debug(conv(h));
        h = (h ^ (h>>6)) % mod;
        cerr << h << " ";debug(conv(h));
        h = (h + (h<<3)) % mod;
        cerr << h << " ";debug(conv(h));
        h = (h ^ (h>>11)) % mod;
        cerr << h << " ";debug(conv(h));
        h = (h + (h<<16)) % mod;
        cerr << h << " ";debug(conv(h));

        debug("rest:");

        vi ans = conv(h);
        debug(ans);
        ans = restoreSum(ans, 16);
        ans = restoreXor(ans, 11);
        ans = restoreSum(ans, 3);
        ans = restoreXor(ans, 6);
        ans = restoreSum(ans, 10);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    while(q-->0) {
        size_t n;
        cin >> n;
        vi ans = conv(n);
        ans = restoreSum(ans, 16);
        ans = restoreXor(ans, 11);
        ans = restoreSum(ans, 3);
        ans = restoreXor(ans, 6);
        ans = restoreSum(ans, 10);
        cout << conv(ans) << "\n";
    }
    return 0;
}
