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

const int mod = int(1e9 + 7.5);

int mul(int x, int y) {
    return int((1ll * x * y) % mod);
}

int modpow(int x, int n) {
    int res = 1;
    while(n > 0) {
        if (n & 1) {
            res = mul(res, x);
            n -= 1;
        } else {
            x = mul(x, x);
            n /= 2;
        }
    }
    return res;
}

int inv(int x) {
    return modpow(x, mod - 2);
}

int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int main() {
    std::ios_base::sync_with_stdio(false);


    int n, k;
    cin >> n >> k;
    string s ;
    cin >> s;
    vi fact(n + 1);
    vi invFact(n + 1);
    vi p10(n + 1);
    for (int i =0 ; i < fact.size(); ++i) {
        if (i == 0) {
            fact[i] = 1;
            p10[i] = 1;
        } else {
            fact[i] = mul(fact[i - 1], i);
            p10[i] = mul(p10[i-1], 10);
        }
        invFact[i] = inv(fact[i]);
    }

    vector<int> sum(1);
    for (char ch: s) {
        int l = sum.back();
        sum.push_back(l + (ch - '0'));
    }

    auto Comb = [&](int N, int K) {
        debug(N);
        debug(K);

        if (N - K < 0) return 0;
        return mul(fact[N], mul(invFact[K], invFact[N - K]));
    };

    //debug(Comb(10, 7));

    int res = 0;
    // last
    for (int i = 0; i < n; ++i) {
        res = add(res, mul(mul(int(s[i] - '0'), p10[n-i-1]),Comb(i, k)));
    }

    debug(res);

    for (int len = 1; len <= n; ++len) {
        if (k > 0)
            res = add(res,
                mul(sum[n - len],
                    mul(p10[len - 1],
                        Comb(n - len - 1, k - 1))));
    }
    cout << res << "\n";


    return 0;
}
