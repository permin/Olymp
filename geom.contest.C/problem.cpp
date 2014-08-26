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
typedef long long ll;
const double EPS = 1e-9;

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
};

//typedef long double Q;

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
};

/*ostream & operator << (ostream & out, const Point& p) {
    return out << "<" << p.x << ", " << p.y << ">";
}*/

struct Line  {
    Q A;
    Q B;
    Q C;
    Q operator()(const Point& P) const {
        return A * P.x + B * P.y + C;
    }
    bool lies(const Point& P) const {
        return (*this)(P) == Q(0);
        //return fabs((*this)(P)) < EPS;
    }
};

Line makeLine(const Point& first, const Point & second) {
    Q u = second.x - first.x;
    Q v = second.y - first.y;
    Line res;
    res.A = v;
    res.B = -u;
    res.C = - (res.A * first.x + res.B * first.y);
    return res;
}

Q det(Q a, Q b, Q c, Q d) {
    return a * d - b * c;
}

bool intersect(const Line& first, const Line& second, Point* res) {
    Q den = det(first.A, first.B, second.A, second.B);
    if (den == Q()) {
    //if (fabs(den) < EPS) {
        return 0;
    }
    res->x = det(-first.C, first.B, -second.C, second.B) / den;
    res->y = det(first.A, -first.C, second.A, -second.C) / den;
    return 1;
}

bool canSee(Point A, Point B,  vector<pair<Point, int> > onLine) {
    if (B < A)
        swap(A, B);
    if (onLine.empty())
        return 0;
    vector<pair<Point, Point> > segs;
    Point beg = onLine[0].first;
    size_t i = 1;
    int bal = 1;
    bool inSeg = true;
    while (i < onLine.size()) {
        bal -= onLine[i].second;
        if (bal == 0 && inSeg) {
            segs.push_back(MP(beg, onLine[i].first));
            inSeg = 0;
        }
        if (bal && !inSeg) {
            beg = onLine[i].first;
            inSeg = 1;
        }
        ++i;
    }
    /*debug(onLine);
    debug(segs);
    debug(A);
    debug(B);*/
    assert(!inSeg);
    for (size_t i = 0; i < segs.size(); ++i) {
        if (segs[i].first <= A && B <= segs[i].second) {
        //debug("true");
            return 1;
        }
    }
    //debug("false");
    return 0;
}

int main () {

    if (0){
        vector<pair<Point, int> > onLine;
        onLine.push_back(MP(Point(Q(0), Q(0)), -1));
        onLine.push_back(MP(Point(Q(1), Q(0)), +1));
        onLine.push_back(MP(Point(Q(3), Q(0)), -1));
        onLine.push_back(MP(Point(Q(5), Q(0)), +1));
        Point A(Q(0), Q(0));
        Point B(Q(2), Q(0));
        cout << canSee(A, B, onLine);
        return 0;
    }
    freopen("guards.in", "r", stdin);
    freopen("guards.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<Point, Point> > ends(n);
    for (int i = 0; i < n; ++i) {
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        ends[i].first.x=Q(a);
        ends[i].first.y=Q(b);
        ends[i].second.x=Q(c);
        ends[i].second.y=Q(d);
        if (ends[i].second < ends[i].first) {
            swap(ends[i].first, ends[i].second);
        }
    }

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Point res;
            Line line1 = makeLine(ends[i].first, ends[i].second);
            Line line2 = makeLine(ends[j].first, ends[j].second);
            if (intersect(line1, line2, &res)) {
                points.push_back(res);
            }
        }
    }
    sort(all(points));
    points.erase(unique(all(points)), points.end());

    vector<vector<size_t> > lineIndex(points.size(), vector<size_t> (points.size(), -1));
    vector<Line> lines;
    for (int i = 0; i < n; ++i) {
        lines.push_back(makeLine(ends[i].first, ends[i].second));
    }
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            for (size_t k = 0; k < lines.size(); ++k) {
                if (lines[k].lies(points[i]) && lines[k].lies(points[j])) {
                    lineIndex[i][j] = k;
                    lineIndex[j][i] = k;
                    break;
                }
            }
        }
    }
    vector<vector<pair<Point, int> > > onLine(lines.size());
    for (size_t i = 0; i < ends.size(); ++i) {
        for (size_t k = 0; k < lines.size(); ++k) {
            if (lines[k].lies(ends[i].first) && lines[k].lies(ends[i].second)) {
                onLine[k].push_back(MP(ends[i].first, -1));
                onLine[k].push_back(MP(ends[i].second, +1));
                break;
            }
        }
    }

    for (size_t k = 0; k < lines.size(); ++k) {
        sort(all(onLine[k]));
    }

    int res = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = i + 1; j < lines.size(); ++j) {
            for (size_t k = j + 1; k < lines.size(); ++k) {
                Point A, B, C;
                bool ok = true;
                ok = ok && intersect(lines[i], lines[j], &A);
                ok = ok && intersect(lines[j], lines[k], &B);
                ok = ok && intersect(lines[k], lines[i], &C);
                if (!ok)
                    continue;
                size_t a,b,c;
                a = lower_bound(all(points), A) - points.begin();
                b = lower_bound(all(points), B) - points.begin();
                c = lower_bound(all(points), C) - points.begin();
                if (lineIndex[a][b] != j ||
                        lineIndex[b][c] != k ||
                        lineIndex[a][c] != i)
                    continue;
                ok = ok && canSee(A, B, onLine[j]);
                ok = ok && canSee(B, C, onLine[k]);
                ok = ok && canSee(A, C, onLine[i]);
                /*if (ok) {
                    cerr << i << " " << j << " " << k << "\n";
                }*/
                res += ok;
            }
        }
    }
    cout << res << "\n";

    return 0;
}
