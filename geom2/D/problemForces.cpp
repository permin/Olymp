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

struct Force {
    virtual Point operator()(const Point& p) const = 0;
    virtual ~Force(){};
};

double sqr(double x) {
    return x * x;
}

double distToOrigin(const Point& p) {
    double res = 0;
    for (size_t i = 0; i < p.size(); ++i) {
        res += sqr(p[i]);
    }
    return sqrt(res);
}

/*struct BoundForce: public Force {
    explicit BoundForce(double R): R(R) {}
    double R;
    Point operator()(const Point& p) const {
        double dist = distToOrigin(p);
        if (fabs(dist - R) < EPS) {
            return {0.0, 0.0, 0.0};
        }
        return -1.0 * (p - p/dist*R)/R * sqrt(fabs((dist - R))) * 1.0;
    }
};*/

struct RandomForce: public Force {
    explicit RandomForce(double a): a(a){
    }
    double a;
    Point operator()(const Point& /*p*/) const {
        return {a * rand() / RAND_MAX, a * rand() / RAND_MAX,a * rand() / RAND_MAX};
    }
};

struct CenterForce: public Force {
    explicit CenterForce(Point p): center(p){
    }
    Point center;
    Point operator()(const Point& p) const {
        return ((p - center) / (1e-9 + distToOrigin(p - center)) / sqr(1e-9 + distToOrigin(p - center))) * 1.0;
    }
};

void apply(vector<Point>& points, vector<Point>& velocities, const vector<Force*>& forces, double dt) {
    std::vector<Point> newVelocities(velocities);
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < forces.size(); ++j) {
            if (j == i)
                continue;
            //debug( (*(forces[j]))(points[i]) );
            //res[i] += (*(forces[j]))(points[i]) * alpha;
            newVelocities[i] += (*(forces[j]))(points[i]) * dt;
        }
    }
    velocities = newVelocities;
    // points = points + velocities * dt;
    for (size_t i = 0; i < points.size(); ++i) {
        points[i] += velocities[i] * dt;
    }
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
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            cerr << distToOrigin(points[i] - points[j]) << " ";
        }
    }
    cerr << "\n";
}

double rs() {
    return (rand() & 1) ? +1 : -1;
}

int main() {
    srand(23);
    int n;
    cin >> n;
    std::vector<Point> points;
    std::vector<Point> velocities;
    double R = 100;
    for (int i = 0; i < n; ++i) {
        points.push_back({rs() * R * rand() / RAND_MAX, rs() * R * rand() / RAND_MAX, rs() * R * rand() / RAND_MAX});
        velocities.push_back({0.0,0.0,0.0});
    }
    debug(points);
    for (int it = 0; it < 10000; ++it) {
        vector<Force*> forces;
        for (size_t i = 0; i < points.size(); ++i) {
            forces.push_back(new CenterForce(points[i]));
        }
        for (auto& x: points) {
            x = x / distToOrigin(x) * R;
        }

        //forces.push_back(new BoundForce(R));
        //forces.push_back(new RandomForce(0.01));//std::max(1e-5, pow(0.3, 1.0 * it))));
        //forces.push_back(new RandomForce(std::max(1e-5, pow(0.3, 1.0 * it))));
        apply(points, velocities, forces, .1);
        //0.1 * rand() / RAND_MAX);//pow(0.999, 1.0 * it));
        //debug(points);
        stat(points);
        debug(velocities);
        for (auto x: forces) {
            delete x;
        }
    }
    stat(points);
    return 0;
}
