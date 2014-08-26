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
#include <iomanip>      // std::setprecision
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

template <class T>
ostream& operator << (ostream& o, const valarray<T>& v) {o << "(";O__(o, v);o << ")";return o;}

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

typedef valarray<double> Point;

double sqr(double x) {
    return x * x;
}

double distToOrigin(const Point& p) {
    double res = 0;
    for (size_t i = 0; i < p.size(); ++i) {
        res += sqr(p[i]);
    }
    assert(res >= 0);
    return sqrt(res);
}

Point d3(const Point& onSpere) {
    assert(onSpere.size() == 2);
    return {
                sin(onSpere[0]) * sin(onSpere[1]),
                sin(onSpere[0]) * cos(onSpere[1]),
                cos(onSpere[0])
           };
}

Point randVector(double h) {
    return {
        2.0 * h * rand() / RAND_MAX - h,
        2.0 * h * rand() / RAND_MAX - h
    };
}

double getAngle(double a, double b, double c) {
    double co = (a*a+b*b-c*c) / 2.0 / a / b;
    return acos(max(-1.0, min(co, 1.0)));
}

double dist(const Point& A, const Point& B) {
    assert(A.size() == 2);
    assert(B.size() == 2);
    Point A3 = d3(A);
    Point B3 = d3(B);
    return getAngle(1,1,distToOrigin(A3-B3));
}

int edges(int vertices) {
    if (vertices == 4)
        return 6;
    if (vertices == 6)
        return 12;
    if (vertices == 8)
        return 12;
    if (vertices == 12)
        return 20;
    if (vertices == 20)
        return 12;
    assert(false);
}

double ROUND;

double f(const vector<Point>& ps) {
    vector<double> pd;
    for (size_t i = 0; i < ps.size(); ++i) {
        for (size_t j = i + 1; j < ps.size(); ++j) {
            //m = min(m, distToOrigin(d3(ps[i])-d3(ps[j])));
            //m = min(m, dist(ps[i],ps[j]));
            //pd.push_back(dist(ps[i],ps[j]));
            pd.push_back(distToOrigin(d3(ps[i])-d3(ps[j])));
            //M = max(M, distToOrigin(d3(ps[i])-d3(ps[j])));
            //res = min(res, dist(ps[i], ps[j]));
        }
    }
    double u = 0.0;
    for (size_t i = 0; i < pd.size(); ++i)
        u += 1.0 / (1e-18 + pd[i]);
    return -u;

    //size_t n = ps.size();
    vector<Point> p3;
    for (size_t i = 0; i < ps.size(); ++i)
        p3.push_back(d3(ps[i]));
    sort(all(pd));
    /*{
        //pd.insert(pd.begin(), -distToOrigin(accumulate(all(p3), Point{0.0, 0.0,0.0})));
        for (auto& x: pd) {
            x = int(0.5 + x * ROUND)/ROUND;
        }
        //pd.erase(pd.begin() + edges(n), pd.end());
        return pd;
    }*/
    return fabs(pd[30] - sqrt(2.0 - 2.0 * cos(acos(-1.0) / 5.0)));
    //return 100.0 * pd[0] - (pd[edges(n) - 1] - pd[0]);

    /*double res = 0.0;
    res +=  1.0 * pd[0] - sqr(pd[edges(n) - 1] - pd[0]);
    return res - 1.30 * distToOrigin(accumulate(all(p3), Point{0.0, 0.0,0.0}));//edges(n) - 1];*/
}

void norm(Point& a) {
    if (a[0] > PI / 2)
        a[0] = PI / 2 - (a[0] - PI / 2);
    if (a[0] < -PI / 2)
        a[0] = -PI / 2 - (a[0] - PI / 2);
    while (a[1] < -PI)
        a[1] += 2.0 * PI;
    while (a[1] > PI)
        a[1] -= 2.0 * PI;
}

void stat(const  std::vector<Point>& points) {
    std::cerr << "---------------------\n";
    debug(points);
    std::cerr << "From O ";
    for (size_t i = 0; i < points.size(); ++i) {
        cerr << distToOrigin(points[i]) << " ";
    }
    cerr << "\n";
    std::cerr << "Pairvise dist ";
    std::vector<double> pd;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            //cerr << distToOrigin(points[i] - points[j]) << " ";
            pd.push_back(distToOrigin(points[i] - points[j]));
        }
    }
    sort(all(pd));
    debug(pd);
    Point cm = accumulate(all(points), Point{0.0,0.0,0.0}) * (1.0 / points.size());
    debug(cm);//accumulate(all(points), Point{0.0,0.0,0.0}) * (1.0 / points.size()));
    cerr << "\n";
}

vector<Point> genRand(int n) {
    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        points.push_back({PI * rand() / RAND_MAX - PI / 2,
                         2.0 * PI * rand() / RAND_MAX - PI});
    }
    return points;
}

void solution(int n) {
    if (n == 8) {
        cout << "8\n"
         "-0.577350 -0.577350 -0.577350\n"
         " 0.577350 -0.577350 -0.577350\n"
         "-0.577350  0.577350 -0.577350\n"
         " 0.577350  0.577350 -0.577350\n"
         "-0.577350 -0.577350  0.577350\n"
         " 0.577350 -0.577350  0.577350\n"
         "-0.577350  0.577350  0.577350\n"
         " 0.577350  0.577350  0.577350\n";
    }
    if (n == 4) {
        cout << "4\n"
        "0.188251 0.584443 0.789296\n"
        "0.237849 0.487562 -0.840066\n"
        "0.545416 -0.835540 0.066284\n"
        "-0.971516 -0.236465 -0.015513\n";
    }
    if (n == 6) {
        cout << "6\n"
        "0.790094 -0.380798 0.480359\n"
        "-0.472421 -0.877614 0.081320\n"
        "-0.790094 0.380798 -0.480359\n"
        "0.390603 -0.291182 -0.873294\n"
        "0.472421 0.877614 -0.081320\n"
        "-0.390603 0.291182 0.873294\n";
    }
    if (n == 12) {
        cout << "12\n";
cout << "0.379158 0.370452 0.847941\n";
cout << "-0.538437 -0.838875 0.079843\n";
cout << "0.421080 -0.836711 -0.350152\n";
cout << "0.988185 -0.089306 0.124559\n";
cout << "-0.379158 -0.370452 -0.847941\n";
cout << "0.306627 -0.665117 0.680881\n";
cout << "-0.421080 0.836711 0.350152\n";
cout << "-0.564346 -0.092807 0.820305\n";
cout << "0.538437 0.838875 -0.079843\n";
cout << "0.564346 0.092807 -0.820305\n";
cout << "-0.988185 0.089306 -0.124559\n";
cout << "-0.306627 0.665117 -0.680881\n";
    }
    if (n == 20) {
        cout << 20 << "\n";
        cout <<  " 0.702180 -0.161064 0.693543 \n";
cout <<  " 0.799417 0.469815 0.374442 \n";
cout <<  " 0.050940 -0.162533 0.985387 \n";
cout <<  " -0.254311 0.467438 0.846657 \n";
cout <<  " 0.208273 0.858251 0.469072 \n";
cout <<  " -0.208273 -0.858251 -0.469072 \n";
cout <<  " 0.079393 -0.981853 0.172222 \n";
cout <<  " -0.799417 -0.469815 -0.374442 \n";
cout <<  " -0.333963 -0.669808 0.663193 \n";
cout <<  " -0.877097 -0.353351 0.325336 \n";
cout <<  " 0.719765 -0.667432 0.190979 \n";
cout <<  " 0.827870 -0.349506 -0.438722 \n";
cout <<  " 0.254311 -0.467438 -0.846657 \n";
cout <<  " 0.877097 0.353351 -0.325336 \n";
cout <<  " -0.050940 0.162533 -0.985387 \n";
cout <<  " -0.702180 0.161064 -0.693543 \n";
cout <<  " -0.827870 0.349506 0.438722 \n";
cout <<  " -0.079393 0.981853 -0.172222 \n";
cout <<  " -0.719765 0.667432 -0.190979 \n";
cout <<  " 0.333963 0.669808 -0.663193 \n";
    }

    exit(0);
}

int main() {
    ROUND = 1e2;
    srand(25);
    int n;
    cin >> n;

    solution(n);
    cerr << setprecision(9);
    //assert(n == 6);
    vector<Point> points;
    vector<Point> bestPoints;
    for (int i = 0; i < n; ++i) {
        bestPoints.push_back({PI * rand() / RAND_MAX - PI / 2,
                         2.0 * PI * rand() / RAND_MAX - PI});
    }
    //debug(points);
    auto bestF = f(bestPoints);
    points = bestPoints;

    double step;
    auto curF = bestF;
    int last = -1e9;
    int restarts = 0;
    for (int it = 0; ; ++it) {
        if (it - last > 40000) {
            std::cerr << "RESTART\n";
            ++restarts;
            std::vector<Point> p3;
            for (int i = 0; i < n; ++i) {
                p3.push_back(d3(bestPoints[i]));
            }
            stat(p3);
            debug(bestF);
            if (restarts == 3)
                break;
            points = genRand(n);
            //points = bestPoints;
            //ROUND *= 2.0;
            //ROUND = min(ROUND, 1e8);
            //for (int i = 0; i < n; ++i)
            //    points[i] += randVector(0.1);
            curF = f(points);
            last = it;
            step = 0.5;
        }
        vector<Point> add;
        for (int i = 0; i < n; ++i) {
            add.push_back(randVector(step));
        }
        vector<Point> np;
        for (int i = 0; i < n; ++i) {
            double q = 1.0 * rand() / RAND_MAX;
            if (q < 0.9)
                np.push_back(points[i] + add[i]);
            else
                np.push_back(points[i]);
        }
        auto nF = f(np);
        if (nF > bestF) {
            bestPoints = np;
            bestF = nF;
        }
        if (nF > curF) {
            points = np;
            curF = nF;
            last = it;
            //debug(curF);
        } else {
            if (1.0 * rand() / RAND_MAX < 0.001) {
                points = np;
                curF = nF;
            }
        }
        if (it - last > 3000)
            step /= 2.0;
        /*if (it % 1000 == 0) {
            step /= 2.0;
        }*/
        //debug(curF);
    }
    std::vector<Point> p3;
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        p3.push_back(d3(bestPoints[i]));
        printf("cout << \"%0.6lf %0.6lf %0.6lf\\n\";\n", p3.back()[0], p3.back()[1], p3.back()[2]);
    }
    stat(p3);

    return 0;
}
