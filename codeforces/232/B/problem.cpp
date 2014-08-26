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

typedef unsigned long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

ll gcd(ll x, ll y) {
    while(x) {
        y %= x;
        swap(x,y);
    }
    return y;
}

ll lcm(ll x, ll y) {
    return (x / gcd(x, y)) * y;
}

struct  Q {
    ll n, d;
    Q(ll n = 0, ll d = 1): n(n), d(d){c();}

    void c() {
        ll x = gcd((n), (d));
        if (x) {
            n/=x;
            d/=x;
        }
    }

    Q operator+(const Q& q) const {
        ll dd = lcm(d, q.d);
        return Q(n * (dd/d) + q.n * (dd/q.d), dd);
    }
};

void out(Q q) {
    q.c();
    cout << q.n << "/" << q.d << "\n";
}

bool isPrime(int n) {
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return 0;
    return 1;
}

void s() {
    int n;
    cin >> n;
    if (n == 2) {
        out(Q(1,6));
        return;
    }
    if (n == 3) {
        out(Q(7,30));
        return;
    }
    debug(n);
    int p1 = n;
    int p2 = n + 1;
    while(!isPrime(p1))
        --p1;
    while(!isPrime(p2))
        ++p2;
    int p0 = 2;
    debug(p0);
    debug(p1);
    debug(p2);
    Q a = Q(p1 - p0, 1ULL * p0 * p1) ;
    Q b = Q((n - p1 + 1), (1ULL * p2) * p1);;
    Q ans = a + b;
    out(ans);
}

int main() {
    int t;
    cin >> t;
    while (t-->0) {
        s();
    }

    return 0;
}

