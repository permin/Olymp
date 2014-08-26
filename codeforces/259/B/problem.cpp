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
const int INF = std::numeric_limits<int>::max() / 3;
const long long LLINF = std::numeric_limits<ll>::max();

vector<int> smallPrimes;

bool isP(int x) {
    if (x < 2)
        return 0;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

bool hasBigPrime(int n) {
    for (int j = 0; j < smallPrimes.size(); ++j) {
        while (n % smallPrimes[j] == 0)
            n /= smallPrimes[j];
    }
    return n != 1;
}

int getMask(int n) {
    int mask = 0;
    for (int j = 0; j < smallPrimes.size(); ++j) {
        if (i % smallPrimes[j] == 0) {
            mask |= 1 << j;
        }
    }
    return mask;
}

int main() {
    for (int i = 2; i <= 30; ++i) {
        if (isP(i)) {
            smallPrimes.push_back(i);
        }
    }
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> s(a);
    sort(all(a));

    vii dp(n+1, vi(1 << smallPrimes.size(), INF));
    vii choice(n, vi(1 << smallPrimes.size(), -1));
    viii choice(n, vii(1 << smallPrimes.size(), vi()));

    viii end(n, vii(1 << smallPrimes.size(), vi()));

    dp[n].assign(1 << smallPrimes.size(), 0);
    return 0;
}

