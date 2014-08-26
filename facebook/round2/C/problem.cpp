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
#include <valarray>

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


const int mod = 1e9 + 7.5;
int mul(int x, int y) {
    return (1LL * x * y) % mod;
}
int add(int x, int y) {
    return (x + y) % mod;
}
int sub(int x, int y) {
    return (x + (mod - y)) % mod;
}
int p2(int n) {
    if (n == 0)
        return 1;
    if (n & 1) {
        return mul(2, p2(n - 1));
    }
    int c = p2(n>>1);
    return mul(c, c);
}

int f(int v, vi& dp, const vii& childs) {
    int &res = dp[v];
    if (res >= 0)
        return res;
    res = p2(childs[v].size() + 1);
    res = sub(res, 1);
    for (int i = 0; i < childs[v].size(); ++i) {
        res = sub(res, f(childs[v][i], dp, childs));
    }
    return res;
}

void solveTest() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i + 1 < n; ++i)  {
        cin >> a[i];
    }
    int res = 1;
    vector<vector<int>> childs(n);
    for (int i = 0; i < n - 1; ++i) {
        int v = i + 1;
        int p = a[i];
        vector<int> dp(v, -1);
        res = mul(res, f(p, dp, childs));
        childs[p].push_back(v);
    }
    cout << res << "\n";
}

int main() {
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        cout << "Case #"<<i+1<<": ";
        solveTest();
    }
    return 0;
}
