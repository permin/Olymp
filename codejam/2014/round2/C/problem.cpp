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

typedef pii Point;
struct Segment {
    Segment(){}
    Segment(Point A, Point B):
        A(A), B(B){}
    Point A,B;
    int maxY() const {
        return max(A.second, B.second);
    }
    int maxX() const {
        return max(A.first, B.first);
    }
    int minY() const {
        return min(A.second, B.second);
    }
    int minX() const {
        return min(A.first, B.first);
    }
    bool isVertical() const {
        return A.first == B.first;
    }
};

struct Rect {
    int x0,y0, x1, y1;
    Rect():
        x0(-1), y0(-1), x1(-1), y1(-1){}
    Rect(int x0, int y0, int x1, int y1):
        x0(x0), y0(y0), x1(x1), y1(y1){}
    vector<Point> vertices() const {
        return {
            Point(x0, y0),
            Point(x0, y1),
            Point(x1, y1),
            Point(x1, y0)
        };
    }
    vector<Segment> edges() const {
        vector<Segment> res;
        vector<Point> v = vertices();
        for (int i = 0; i < 4; ++i) {
            int j = (i + 1) % 4;
            res.emplace_back(v[i], v[j]);
        }
        return res;
    }
};

int distance(const Point& A, const Point& B) {
    if (A == B)
        return 0;
    if (A.first == B.first)
        return abs(A.second - B.second);
    if (A.second == B.second)
        return abs(A.first - B.first);
    int dx =  abs(A.first - B.first) ;
    int dy = abs(A.second - B.second);
    return max(dx, dy);
    //return abs(A.first - B.first) + abs(A.second - B.second) - 1;
}

int distance(const Point& O, const Segment& s) {
    int res = INF;
    res = min(res, distance(O, s.A));
    res = min(res, distance(O, s.B));
    if (s.isVertical()) {
        if (s.minY() <= O.second && O.second <= s.maxY()) {
            res = min(res, abs(O.first - s.minX()));
        }
    } else {
        if (s.minX() <= O.first && O.first <= s.maxX()) {
            res = min(res, abs(O.second- s.minY()));
        }
    }
    return res;
}
int distance(const Segment& s, const Point& O) {
    return distance(O, s);
}
int distance(const Segment& s, const Segment& s1) {
    int res = INF;
    res = min(res,distance(s.A, s1.A));
    res = min(res,distance(s.A, s1.B));
    res = min(res,distance(s.B, s1.A));
    res = min(res,distance(s.B, s1.B));
    return res;
}

int distance(const Segment& s, const Rect& r) {
    int res = INF;
    auto v = r.vertices();
    auto e = r.edges();
    for (int i = 0; i < 4; ++i) {
        res = min(res, distance(s,v[i]));
        res = min(res, distance(s,e[i]));
    }
    return res;
}

int distance(const Rect& r, const Segment& s) {
    return distance(s,r);
}

int distance(const Rect& R1, const Rect& R2) {
    auto v1 = R1.vertices();
    auto v2 = R2.vertices();
    auto e1 = R1.edges();
    auto e2 = R2.edges();
    int res = INF;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            res = min(res, distance(v1[i], v2[j]));
            res = min(res, distance(e1[i], v2[j]));
            res = min(res, distance(v1[i], e2[j]));
        }
    return res;
}

int sh(const vector<vector<pii>>& al, int source, int target) {
    vector<int> dist(al.size(), INF / 2);
    set<pii> Q;
    dist[source] = 0;
    Q.insert(pii(0, source));
    while (!Q.empty()) {
        int v = Q.begin()->second;
        Q.erase(Q.begin());
        for (int i = 0; i < al[v].size(); ++i) {
            int v2 = al[v][i].first;
            int d = al[v][i].second;
            if (dist[v2] > dist[v] + d) {
                Q.erase(pii(dist[v2], v2));
                dist[v2] = dist[v] + d;
                Q.insert(pii(dist[v2], v2));
            }
        }
    }
    return dist[target];
}

void solveTest(int cas) {
    if (cas == 70)
        cerr << "1\n";
    int w,h,n;
    cin >> w >> h >> n;
    if (cas == 70)
        cerr << w << " " << h << " " << n << "\n";
    vector<Rect> r(n);

    for (int i =0 ; i < n; ++i) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        r[i] = Rect(a,b,c+1,d+1);
    }
    Segment left(Point(0,0), Point(0, h));
    Segment right(Point(w, 0), Point(w, h));
    vector<vector<pii>> al(n + 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            al[i].push_back(pii(j, distance(r[i], r[j])));
        }
        al[n].push_back(pii(i, distance(left, r[i])));
        al[i].push_back(pii(n, distance(left, r[i])));
        al[n+1].push_back(pii(i, distance(right, r[i])));
        al[i].push_back(pii(n+1, distance(right, r[i])));
    }
    al[n].push_back(pii(n+1, w));
    al[n+1].push_back(pii(n, w));
    //debug(al);
    int res =  sh(al, n, n+1) ;
    cout << res << "\n";
}

int main() {
    if(0){
       debug(distance(Point(0,0), Point(0,10)));
       debug(distance(Point(0,0), Point(2,10)));
       debug(distance(Point(0,0), Segment(Point(10,10), Point(10, -10))));
       debug(distance(Point(0,0), Segment(Point(10,-1), Point(10, -10))));
       debug(distance(Rect(0,0, 1,1), Rect(2,2,3,3)));
       //debug(distance(Rect(2, 0, 2, 0), Rect(0, 2, 0, 2)));
       debug(Rect(1,2,3,4).vertices());
       //debug(Rect(1,2,3,4).edges());
    }
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #" << t + 1 << ": ";
        solveTest(t);
    }
    return 0;
}
