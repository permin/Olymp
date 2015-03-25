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

template <class T>
ostream& operator << (ostream& o, const valarray<T>& v) {o << "(";for(int i = 0; i < v.size(); ++i) {if (i) o << ", "; o << v[i]; };o << ")";return o;}

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

valarray<ll> primes;
const int X = 1e9 + 7.5;
//const int X = 10;//1e9 + 7.5;

typedef valarray<ll> Hash;

namespace std {
    template<> struct hash<Hash> {
        size_t operator()(const Hash& h) const {
            ll r = 0;
            for (int i = 0 ;i < h.size(); ++i)
                r = r * (X + 20000) + h[i];
            return r;
        }
    };
}

bool isPrime(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return 0;
    return 1;
}

int mul(int x, int y, int mod) {
    return (1LL *x * y) % mod;
}

int myPow(int x, int n, int mod) {
    if (n == 0)
        return 1 % mod;
    if (n & 1) {
        return mul(x, myPow(x, n - 1, mod), mod);
    } else {
        int c = myPow(x, n / 2, mod);
        return mul(c, c, mod);
    }
}

valarray<ll> add(valarray<ll> v, int x) {
    //v *= X;
    //v %= primes;
    Hash xx(primes.size());
    for (int i = 0; i  < primes.size(); ++i)
        xx[i] = myPow(X, x, primes[i]);
    v += xx;
    v %= primes;
    return v;
}

struct Eq {
    bool operator()(const Hash& h1, const Hash& h2) const {
        for (int i = 0; i< h1.size(); ++i) {
            if (h1[i] != h2[i])
                return false;
        }
        return true;
    }
};

void solveTest() {
    int n, m;
    int x1, a1, b1, c1, r1;
    int x2, a2, b2, c2, r2;
    cin >> n >> m >>
        x1 >> a1 >> b1 >> c1 >> r1 >>
        x2 >> a2 >> b2 >> c2 >> r2;
    vector<int> Board1(n);
    vector<int> Board2(m);
    Board1[0] = x1;
    Board2[0] = x2;
    for (int i = 1; i < m || i < n; ++i) {
        if (i < n)
            Board1[i] = (1LL * a1 * Board1[(i-1) % n] + 1LL * b1 * Board2[(i-1) % m] + c1) % r1;
        if (i < m)
            Board2[i] = (1LL * a2 * Board1[(i-1) % n] + 1LL * b2 * Board2[(i-1) % m] + c2) % r2;
    }
    set<int> set1, set2;
    vector<Hash> pref1, pref2;
    Hash h1(primes.size());
    Hash h2(primes.size());
    for (int i = 0; i < n; ++i) {
        if (set1.count(Board1[i]) == 0)
            h1 = add(h1, Board1[i]);
        set1.insert(Board1[i]);
        pref1.push_back(h1);
    }
    for (int i = 0; i < m; ++i) {
        if (set2.count(Board2[i]) == 0)
            h2 = add(h2, Board2[i]);
        set2.insert(Board2[i]);
        pref2.push_back(h2);
    }
    unordered_map<Hash, int, std::hash<Hash>, Eq> count1;
    for (int i = 0; i < n; ++i) {
        count1[pref1[i]] += 1;
    }
    ll res = 0;
    for (int i = 0; i < m; ++i) {
        res += count1[pref2[i]];
    }
    cout << res << "\n";
}

int main() {

    primes.resize(4);
    int j = 0;
    for (int i = 1e9 + 10; j < primes.size(); ++i)  {
        if (isPrime(i))
            primes[j++] = i;
    }

    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        cout << "Case #"<<i+1<<": ";
        solveTest();
    }
    return 0;
}
