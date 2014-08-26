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

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

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

const int mod = 1e9+7;

int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int sub(int x, int y) {
    if (y == 0)
        return x;
    return add(x, mod - y);
}

ll mul(int x, int y) {
    return (1LL *x * y) % mod;
}

void solveTest() {
    int n;
    cin >> n;
    vii dp(n + 2, vi(n, 0));
    dp[1][0] = 1;
    dp[2][0] = 1;

    for (int len = 3; len <= n; ++len) {
        int sumA = 0;
        int sumB = 0;
        for (int j = 1; j < len; ++j) {
            sumB = add(sumB, mul(dp[len-2][j-1], len-j-1));
        }
        dp[len][0] = sumB;
        for (int i = 1; i < len; ++i) {
            {
                int j = i - 1;
                sumA = add(sumA, dp[len-2][j]);
            }
            {
                int j = i;
                sumB = sub(sumB,  mul(dp[len-2][j-1], len-j-1));
            }
            dp[len][i] = add(sumB, mul(sumA, len-i-1));
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i)
        res = add(res, dp[n][i]);
    cout << res << "\n";
}

int main() {
    solveTest();
    return 0;
}

