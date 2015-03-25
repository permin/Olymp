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
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;};

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

double area;
double a_x[4];
double a_y[4];

inline double dist(double phi, const pii& A) {
    int x = A.first;
    int y = A.second;
    return x * sin(phi) - y * cos(phi);
}

void g(double phi, const vector<pii>& points, double& min_val, double &max_val) {
    vector<double> a;
    a.reserve(a.size());
    for (int i = 0 ;i < points.size(); ++i) {
        a.push_back(dist(phi, points[i]));
    }
    /*{
        auto it = max_element(all(a));
        max_val = it->first;
    }
    {
        auto it = min_element(all(a));
        min_val = it->first;
    }*/
    auto its = minmax_element(all(a));
    min_val = *its.first;
    max_val = *its.second;
}

double solve(double phi, const vector<pii>& points) {
    double a,b,c,d;

    g(phi, points,a,b);
    g(phi + PI / 2 , points, c, d);

    double ex = sin(phi);
    double ey = -cos(phi);

    double fx = sin(phi + PI / 2);
    double fy = -cos(phi + PI / 2);

    if (area > fabs(b -a) * fabs(c - d)) {
        area = fabs(b -a) * fabs(c - d);

        //std::cerr << a << " " << b << " " << c << " " << d << "\n";

        a_x[0] = ex * a + fx * c;
        a_y[0] = ey * a + fy * c;

        a_x[3] = ex * a + fx * d;
        a_y[3] = ey * a + fy * d;

        a_x[1] = ex * b + fx * c;
        a_y[1] = ey * b + fy * c;

        a_x[2] = ex * b + fx * d;
        a_y[2] = ey * b + fy * d;

    }

    return fabs(b -a) * fabs(c - d);
}

void search(double lo, double up, const vector<pii>& points, int its) {
    const double phi = (1.0 + sqrt(5.0)) / 2.0;
    const double resphi = 2.0 - phi;

    double d = up - lo;
    double m1 = lo + resphi * d;
    double m2 = up - resphi * d;
    double f1 = solve(m1, points);
    double f2 = solve(m2, points);

    for (int it = 0; it < its; ++it) {
        if (f1 < f2) {
            up = m2;
            m2 = m1;
            f2 = f1;
            m1 = lo + resphi* (up - lo);
            f1 = solve(m1, points);
        } else {
            lo = m1;
            m1 = m2;
            f1 = f2;
            m2 = up - resphi *(up - lo);
            f2 = solve(m2, points);
        }
        //if (fabs(f1- f2) < 1e-5)
        //    break;
        /*if (f1 < f2) {
            up = m2;
        } else {
            lo = m1;
        }*/
    }
    area=min(area, solve(lo, points));
}

int main() {
    int n ;
    cin >> n;
    vector<pii> points(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &points[i].first, &points[i].second);
    }

    area = 1e92;
    const int M = 40;
    int best_it = 0;
    for (int i = 0; i < M; ++i) {
        double d = PI / 2.0 / M;
        double aa = area;
        search(d * i, d * i + d, points, 10);
        if (aa != area)
            best_it = i;
    }

    double d = PI / 2.0 / M;
    search(d * best_it, d * best_it + d, points, 100);


    //cout << area << "\n";
    //printf("Area: %0.18lf\n", area);
    for (int i = 0; i < 4; ++i) {
        //cout << a_x[i] << " " << a_y[i] << "\n";
        printf("%0.18lf %0.18lf\n", a_x[i], a_y[i]);
    }

    return 0;
}
