#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <complex>
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
#include <boost/algorithm/string/split.hpp>

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
const double EPS = 1e-1;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

ll gcd(ll a, ll b) {
    while(a) {
        b %= a;
        swap(a, b);
    }
    return b;
}

ll lcm(ll a, ll b) {
    return a * (b / gcd(a, b));
}

struct Q {
    ll num;
    ll den;
    double val;
    Q(ll a=0, ll b=1): num(a), den(b){c();};
    Q(const Q& q): num(q.num), den(q.den), val(q.val) {c();};
    void c() {
        ll d = gcd(abs(num), abs(den)); num /= d; den /= d;
        if (den < 0) {
            den *= -1;
            num *= -1;
        }
    }
    Q operator + (const Q& q) const {
        ll d = 1;
        ll l = den * q.den;
        return Q(num * (q.den/d) + q.num * (den/d), l);
    }
    Q operator - (const Q& q) const {
        return (*this) + (-q);
    }
    Q operator * (const Q& q) const {
        return Q(num * q.num, den * q.den);
    }
    Q& operator *= (const Q& q) {
        return *this = Q(num * q.num, den * q.den);
    }
    Q& operator /= (const Q& q) {
        return *this = (*this) / q; //Q(num * q.num, den * q.den);
    }
    Q operator / (const Q& q) const {
        return Q(num * q.den, den * q.num);
    }
    bool operator<(const Q& q) const {
        return num * q.den < q.num * den;
    }
    bool operator==(const Q& q) const {
        return !(q < *this || *this < q);
    }
    bool operator!=(const Q& q) const {
        return !(q == *this);
    }
    Q operator-() const {
        return Q(-this->num, this->den);
    }
};

struct Point {
    Point (){}
    Point(Q A, Q B) {
        x = A;
        y = B;
    }
    Q x, y;
    bool operator < (const Point& p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
    bool operator <= (const Point& p) const {
        return p > *this || *this == p;
    }
    bool operator > (const Point& p) const {
        return p < *this;
    }
    bool operator >= (const Point& p) const {
        return p < *this || *this == p;
    }
    bool operator == (const Point& p) const {
        return !(p < *this || *this < p);
    }
    bool operator != (const Point& p) const {
        return !(*this == p);
    }
};

Point inv(Point A) {
    return Point(A.x/ (A.x * A.x + A.y * A.y), A.y/ (A.x * A.x + A.y * A.y));
}

const int MOD = 1e9 + 7;

int mul(int x, int y) {
    return (1LL * x * y) % MOD;
}
int add(int x, int y) {
    return (x + y) % MOD;
}
int sub(int x, int y) {
    return add(x, MOD - y);
}
int mpow(int x, int n) {
    if (n == 0)
        return 1;
    if (n & 1) {
        return mul(x, mpow(x, n - 1));
    }
    int c = mpow(x, n / 2);
    return mul(c,c);
}

int calc(const vector<pair<Point, Point>>& sum, int beg, int end) {
    int res = 1;
    int b = beg;
    int m = 1;
    for (int i = beg; i != end; ++i) {
        if (sum[i].second != sum[b].second) {
            ++m;
            res = mul(res, 1 + i - b);
            b = i;
        }
    }
    res = mul(res, 1 + end - b);
    res = sub(res, m + 1);
    return res;
}

Q Abs(const Q& q) {
    if (q < Q())
        return -q;
    return q;
}

Point NORM(Point p) {
    if (p.x != Q(0)) {
        p.y /= p.x;
        p.x /= p.x;
    } else {
        p.y /= p.y;
    }
    p.x.c();
    p.y.c();
    return p;
}

int main() {
    {
        using namespace boost;
        typedef vector< string > split_vector_type;

        split_vector_type SplitVec; // #2: Search for tokens
        split( SplitVec, "  hello   world  ", [](char ch) {return ch == ' ';}, token_compress_off );
        debug(SplitVec);
        exit(0);
    }
    int n;
    cin >> n;
    vector<Point> p;
    for (int i = 0; i < n; ++i) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        p.push_back(Point(Q(a*51,b),Q(c*51,d)));
    }
    vector<Point> pi;
    for (int i = 0; i < n; ++i) {
        pi.push_back(inv(p[i]));
    }
    vector<pair<Point, Point>> sum;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            sum.push_back(make_pair(
                        Point(pi[i].x+pi[j].x, (pi[i].y+pi[j].y)),
                        NORM(Point(pi[i].x-pi[j].x, pi[i].y-pi[j].y))));
        }
    }
    sort(all(sum));
    sum[sum.size()].first.x.den = 1;
    int beg = 0;
    int res = 0;
    size_t i = 0;
    for (i = 0; i < sum.size(); ++i) {
        if (sum[i].first != sum[beg].first) {
            res = add(res, calc(sum, beg, i));
            //res = sub(res, 1 + i - beg);
            beg = i;
        }
    }
    res = add(res, calc(sum, beg, sum.size()));
    //res = sub(res, 1 + sum.size() - beg);
    cout << res << "\n";
    return 0;
}
