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

const int mod = 1e9 + 7.5;
const int inv2 = mod / 2 + 1;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int countInv(const vi& p) {
    int r = 0;
    for (int i = 0; i < p.size(); ++i) {
        for (int j = i + 1; j < p.size(); ++j) {
            r += (p[i] > p[j]);
        }
    }
    return r;
}

int solve(const vi& pp) {
    vi p(pp);
    sort(all(p));
    int t = 0;
    do {
        t += countInv(p);
        //if (p == pp)
        //    break;
    } while(std::next_permutation(all(p)));
    return t;
}

int main() {
    int n;
    cin >> n;
    vi p(n);
    for (int i = 0; i < n; ++i)
       // cin >> p[i];
       p[i] = i;

    vi factor(n, 1);
    for (int i = 1; i < n; ++i) {
        factor[i] = mul(i, factor[i-1]);
    }
    debug(factor);

    vector<int> s(n);
    for (int i = 1; i < n; ++i) {
        //s[i] = mul(mul(i, mul(i - 1, inv2)), add(s[i-1], factor));
        s[i] = add(
                    mul(s[i-1],i),
                    mul(factor[i - 1], mul(i, mul(i - 1, inv2))));
    }
    debug(s);

    int res = 0 ;
    for (int i = 0; i < n; ++i) {
        res = add(res, mul((p[i] - 1) ,s[n - 1 - i]));
    }
    cout << res << "\n";
    debug(solve(p));

    return 0;
}

