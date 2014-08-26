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
#include <memory>

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

ll gcd(ll A, ll B) {
    if (A < 0)
        A = -A;
    if (B < 0)
        B = -B;
    while (A) {
        B %= A;
        swap(A, B);
    }
    return B;
}

class CC {
public:
    explicit CC(std::unique_ptr<vi>&& p):
        p_(std::move(p)){}
    std::unique_ptr<vi>  get() {
        return std::move(p_);
    }
    std::unique_ptr<vi> p_;
};

int main() {
    {
        CC A(std::unique_ptr<vi>(new vi(4, 123)));
        std::unique_ptr<vi> pp = A.get();
        debug(*pp);
        std::unique_ptr<vi> ppp = A.get();
        debug(*ppp);
        debug(*A.get());
    }

    /*int n,m,C,H,k;
    cin >> n >> m >> C >> H >> k;
    vector<int> c(n);
    vector<int> h(m);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> h[i];
    }

    if (H == C) {
        for (int i = 0; i < k; ++i) {
            cout << "YES\n";
        }
        return 0;
    }
    vector<pii> q(k);
    vector<bool> res(k);
    for (int i = 0; i < k; ++i) {
        int p, q;
        cin >> p >> q;
        if (1LL * q * C == p) {
            res[k] = 1;
            continue;
        }
        ll A = p - 1LL * q * H;
        ll B = q * C - p;
        ll d = gcd(A, B);
        A /= d;
        B /= d;
        if (A > 100*1000 || B > 100*1000) {
            continue;
        }
        res[i] = pii(A, B);
    }


*/
    return 0;
}

