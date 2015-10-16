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
typedef vector<ll> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = 3LL * INF;

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

struct MinLin {
    vi a;
    vi b;
    vi till;
    void add(ll aa, ll bb) {
        assert(a.empty() || a.back() < aa);
        while(!till.empty()) {
            ll x = till.back();
            if (a.back() * x + b.back() >= aa * x + bb) {
                a.pop_back();
                b.pop_back();
                till.pop_back();
            } else {
                break;
            }
        }
        if (till.empty()) {
            till.push_back(LLINF);
        } else {
            if (a.back() == aa) {
                return;
            }
            if (b.back() - bb < 0) {
                till.push_back((b.back() - bb + 1 - aa + a.back()) / (aa - a.back()));
            } else {
                till.push_back((b.back() - bb) / (aa - a.back()));
            }
        }
        a.push_back(aa);
        b.push_back(bb);
    }
    ll req(ll x) {
        size_t pos = lower_bound(till.rbegin(), till.rend(), x) - till.rbegin();
        pos = a.size() - 1 - pos;
        assert(x <= till[pos]);
        assert(pos + 1 == till.size()|| till[pos + 1] < x);
        return a[pos] * x + b[pos];
    }
};

ll dp[5001][3001];

int main() {
    std::ios_base::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vi f(N);
    for (int i = 0; i < N; ++i) {
        cin >> f[i];
    }
    vi sigma(N + 1);
    vi sum(N + 1);

    for (int i = N - 1; i >= 0; --i) {
        sum[i] = f[i] + sum[i+1];
        sigma[i] = sum[i] + sigma[i+1];
    }

    for (int m = 0; m <= M; ++m) {
        MinLin minLin;
        int K = 0;
        if (m == 0) {
            for (int n = 1; n <= N; ++n) {
                dp[n][m] = LLINF;
            }
        } else {
            std::function<void(int,int,int,int)> solveFor =
            [&](int lower, int upper, int minK, int maxK) {
                if (lower >= upper)
                    return;
                int med = (lower + upper) / 2;
                ll& res = dp[med][m];
                res = LLINF;
                int K = 0;
                for (int k = minK; k <= maxK; ++k) {
                    ll cur = dp[k][m - 1] + sigma[k] + k * sum[med] - sigma[med] -
                                med * sum[med];
                    if (cur < res) {
                        K = k;
                        res = cur;
                    }
                }
                solveFor(lower, med, minK, K);
                solveFor(med + 1, upper, K, maxK);
            };
            solveFor(0, N + 1, 0, N);
        }
        continue;
        for (int n = 0; n <= N; ++n) {
            ll& res = dp[n][m];
            if (n == 0) {
                res = 0;
            } else {
                res = LLINF;
                //if (!minLin.a.empty()) {
                //    res = min(res, minLin.req(sum[n]) - sigma[n] - n * sum[n]);
                //}
            }
            if (m != 0) {
                minLin.add(n, dp[n][m-1] + sigma[n]);
            } else {
                continue;
            }


            for (int k = K; k < n; ++k) {
                if (res >
                        dp[k][m - 1] + sigma[k] + k * sum[n] - sigma[n] - n * sum[n]) {
                    res =
                        dp[k][m - 1] + sigma[k] + k * sum[n] - sigma[n] - n * sum[n];
                    K = k;
                }
            }
            /*for (int k = 0; k < n; ++k) {
                res = min(res,
                        dp[k][m - 1] + sigma[k] + k * sum[n] - sigma[n] - n * sum[n]);
            }*/

        }
    }

    debug(sigma[2]);
    debug(sigma[3]);
    debug(sum[3]);
    debug(dp[2][1]);
    debug(dp[3][2]);
    cout << dp[N][M] << "\n";
    return 0;
}
