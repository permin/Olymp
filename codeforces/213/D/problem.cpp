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
#include <unordered_map>
#include <functional>
#include <bitset>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

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

const int MOD = 1e9 + 7;

int add(int x, int y) {
    int r = x + y;
    if (r >= MOD)
        return r - MOD;
    return r;
}

int dp[1001][20001];

int main() {
    const int C = 10000;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    dp[n][C] = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int x = -C; x <= C; ++x) {
            for (int sign = -1; sign <= +1; sign += 2) {
                int nx = x + sign * a[i];
                if (nx < -C || nx > C)
                    continue;
                dp[i][C + x] = add(dp[i][C + x], dp[i + 1][C + nx]);
                if (nx == 0)
                    dp[i][C + x] = add(dp[i][C + x], 1);
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = add(res, dp[i][C]);
    }
    cout << res << "\n";
    return 0;
}
