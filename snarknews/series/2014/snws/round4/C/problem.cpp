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

const int maxN = 2 * 1e6 + 10;
int phi_dp[maxN];
int divisor[maxN];
char isPrime[maxN];

int phi(int x) {
    if (x == 1)
        return 1;
    if (phi_dp[x] >= 0)
        return phi_dp[x];
    if (divisor[x] == -1) {
        return  phi_dp[x] = x - 1;
    }
    int y = x / divisor[x];
    int mul;
    if (y % divisor[x] == 0)
        mul = divisor[x];
    else
        mul = divisor[x] - 1;
    return phi_dp[x] = mul * phi(y);
}

ll solve(int n, int k) {
    ll res = 0;
    if ((k & 1) == 0) {
        return 0;
    }
    k /= 2;
    if (k == 0) {
        return -1;
    }

    ll add = 0;
    if (k == n)
        res += 3;

    for (int a = 2; a <= n; ++a) {
        debug(a);
        if ((n / a) == k) {
            add += phi(a);
        }
    }


    res += add * 4;

    if (res > 1000000000000LL)
        res = -1;
    return res;
}

int gcd(int x, int y) {
    while (x > 0) {
        y %= x;
        swap(x,y);
    }
    return y;
}

int main() {

    for (int i = 0; i < maxN; ++i) {
        phi_dp[i] = -1;
        divisor[i] = -1;
        isPrime[i] = true;
    }

    for (int i = 2; i < maxN; ++i) {
        if (!isPrime[i])
            continue;
        int j = i + i;
        while(j < maxN) {
            isPrime[j] = 0;
            divisor[j] = i;
            j += i;
        }
    }


    //for (int i = 1; i < 100; ++i)
    //    cerr << i << " " << divisor[i] << " " << phi(i) << "\n";

    int n, k;
    cin >> n >> k;
    cout << solve(n, k) << "\n";
    return 0;
}
