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

vector<ll> primes;
double min_log;
double cur_log;

vi a;
vi best_a;

void rec(int , int n) {
    if (n == 1) {
        if (cur_log < min_log) {
            best_a = a;
            min_log = cur_log;
        }
        return;
    }
    double prime_log = std::log(primes[a.size()]);
    for (int i = 1; i * i <= n; ++i) {
        if (n % i)
            continue;
        if (i > 1) {
            cur_log += (i - 1) * prime_log;
            a.push_back(i - 1);
            rec(i, n / i);
            cur_log -= (i - 1) * prime_log;
            a.pop_back();
        }

        int x = n / i;
        cur_log += (x - 1) * prime_log;
        a.push_back(x - 1);
        rec(x, n / x);
        cur_log -= (x - 1) * prime_log;
        a.pop_back();
    }
}

const ll MOD = ll(1e9+9.2);

ll mul(ll x, ll y) {
    ll res = 1LL * x * y;
    res %= MOD;
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    {
        for (int p = 3; p < 1000; ++p) {
            bool ok = 1;
            for (int i = 2; i *i <= p; ++i) {
                if (p % i == 0)
                    ok = 0;
            }
            if (ok)
                primes.push_back(p);
        }
    }

    cur_log = 0;
    min_log = 1e99;

    rec(INF, n);
    //debug(cur_log);

    ll res = 1;
    for (int i = 0; i < best_a.size(); ++i) {
        for (int j = 0; j < best_a[i]; ++j) {
            res = mul(res, primes[i]);
        }
    }
    cout << res << "\n";


    return 0;
}
