//Rodion
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

const int mod = 1e9 + 7.4;

int inv(int x);

int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int C(int n, int k) {
    int res = 1;
    for (int i = 1; i <= k; ++i) {
        res = mul(res, mul(n - i + 1, inv(i)));
    }
    return res;
}

int f(int x, int n) {
    return C(x+n-1,n-1);
}

int inv(int x) {
    int n = mod - 2;
    int res = 1;
    while (n) {
        if (n & 1) {
            res = mul(res, x);
            n ^= 1;
        } else {
            x = mul(x, x);
            n >>= 1;
        }
    }
    return res;
}

int main() {
    C(6,3);
    map<int, int> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vector<int> p;
        for (int i = 2; i * i <= x; ++i) {
            while (x % i == 0) {
                p.push_back(i);
                x /= i;
            }
        }
        if (x != 1) {
            p.push_back(x);
        }
        for (int y: p)
            s[y] += 1;
    }
    int res = 1;
    for (auto pn: s) {
        res = mul(res, f(pn.second, n));
    }
    cout << res << "\n";
    return 0;
}

