/* Team: moscow04 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <deque>
#include <queue>
#include <string>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>

#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

#define DEBUG

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)((a).size()))
#define pb push_back
#define MP make_pair
#define mp MP

#ifdef DEBUG
    #define debug(x) cerr << #x << ": " << (x) << endl;
#else
    #define debug(x) ;
#endif

typedef pair<int, int> pii;
//typedef long long ll;
typedef __int128 ll;

template <typename T> T sqr (T x) {return x * x;}
template <typename T> T abs (T x) {return x > 0 ? x : -x;}

template <typename T>
ostream & operator << (ostream & out, vector<T> const & a) {
    out << "[";
    for (int i = 0; i < sz(a); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << a[i];
    }
    out << "]";
    return out;
}

template <typename T1, typename T2>
ostream & operator << (ostream & out, pair<T1, T2> const & p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

void showTime () {
#ifdef DEBUG
    static double prev;
    static bool first = true;

    double curr = (double)clock() / CLOCKS_PER_SEC;

    cerr.setf(ios::fixed);
    cerr.precision(3);
    cerr << "<";
    if (!first) {
        cerr << curr - prev << "sec, ";
    }
    cerr << curr << "sec>\n";

    first = false;
    prev = curr;
#endif
}

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
        //ll d = gcd(q.den, den);
        //ll l = lcm(q.den, den);
        ll d = 1;
        ll l = den * q.den;
        return Q(num * (q.den/d) + q.num * (den/d), l);
    }
    Q operator -= (const Q& q) {
        return (*this) += (-q);
    }
    Q operator += (const Q& q) {
        (*this) = (*this) + q;
        return (*this);
    }
    Q operator - (const Q& q) const {
        return (*this) + (-q);
    }
    Q operator * (const Q& q) const {
        return Q(num * q.num, den * q.den);
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
    Q operator-() const {
        return Q(-this->num, this->den);
    }
    double d() const {
        return 1.0 * num / den;
    }
};

typedef complex<Q> C;

Q readQ() {
    string s;
    cin >> s;
    s.erase(s.begin() + s.find('.'));
    stringstream o;
    o << s;
    long long x;
    o >> x;
    return Q(x);
}

C Pow(const C& q, int n) {
    if (n == 0) {
        return C(1);
    } else {
        if (n & 1) {
            return q * Pow(q, n ^ 1);
        } else {
            C c = Pow(q, n >> 1);
            return c * c;
        }
    }
}

int main () {
    //freopen("input.txt", "r", stdin);
    C I(0, 1);
    int n;
    cin >> n;
    vector<C> b;
    for (int i = 0; i < n; ++i) {
        // double x, y;
        // cin >> x >> y;
        Q x, y;
        x = readQ(); y = readQ();
        b.push_back(C(x, y));
    }

    C sum;
    for (int i = 0; i < n; ++i) {
        sum += Pow(I, n - 1 - i) * b[i];
    }
    sum *= (C(1) - I);
    C c1 = Pow(I, n) - C(1);

    if (c1 == C(0)) {
        if (sum  == C(0)) {
            cout << "-1";
        } else {
            cout << "-2";
        }
    } else {
        C A1 = -sum / c1;
        vector<C> a(1, A1);
        for (int i = 1; i < n; ++i) {
            a.push_back(I * a[i - 1] + b[i-1] * (C(1) - I));
        }
        cout << n << "\n";
        for (int i = 0; i < n; ++i) {
            printf("%0.18lf %0.18lf\n", 1e-4 * a[i].real().d(), 1e-4 * a[i].imag().d());
        }
    }


    return 0;
}
