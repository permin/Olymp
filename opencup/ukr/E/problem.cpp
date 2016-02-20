#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": " << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template <class F, class S>
ostream &operator<<(ostream &o, const pair<F, S> &p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C> void O__(ostream &o, const C &c) {
  bool f = 1;
  for (const auto &x : c) {
    if (!f) {
      o << ", ";
      f = 0;
      o << x;
    }
  }
}
template <class T> ostream &operator<<(ostream &o, const vector<T> &v) {
  o << "[";
  O__(o, v);
  o << "]";
  return o;
}

template <class T, class V>
ostream &operator<<(ostream &o, const map<T, V> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

template <class T> ostream &operator<<(ostream &o, const set<T> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

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

typedef std::complex<double> Point;

bool fail;

Point mod1(double phi) { return std::polar(1.0, phi); }

double ra() { return 1.0 * rand() / RAND_MAX; }
bool test(const vector<Point> &points);

vector<Point> generateInitPoints(int n) {
  vector<double> args(n);
  for (int i = 0; i < n; ++i) {
    args[i] = 2.0 * PI * i / n;
    double x = 2.0 * PI / n * 0.0001;
    // double x = 2.0 * PI / n * 0.08;
    args[i] -= x;
    args[i] += ra() * 2 * x;

    // args[i] = 2.0 * PI / n * ra();
  }
  sort(all(args));
  vector<Point> res;
  for (int i = 0; i < n; ++i) {
    res.push_back(mod1(args[i]));
  }
  return res;
}

double dist(const Point &z1, const Point &z2) { return std::abs(z1 - z2); }

vector<double> distances(const vector<Point> &z) {
  int n = z.size();
  vector<double> res;
  for (int i = 0; i < n; ++i) {
    res.push_back(dist(z[i], z[(i + 1) % n]));
  }
  return res;
}

vector<Point> homot(vector<Point> z) {
  auto d = distances(z);
  double scale = *max_element(all(d));
  for (auto &x : z) {
    x /= scale;
  }
  return z;
}

Point rotate(const Point &z, double phi) { return z * mod1(phi); }

Point rotate(const Point &z, const Point &o, double phi) {
  return o + rotate(z - o, phi);
}

void make_rotation(vector<Point> &points, int i, int j, double phi) {
  int k = i;
  while (k != j) {
    points[k] = rotate(points[k], points[i], phi);
    ++k;
    if (k == points.size()) {
      k = 0;
    }
  }
  points[j] = rotate(points[j], points[i], phi);
}

// C
double angle(double a, double b, double c) {
  double cos_phi = a * a + b * b - c * c;
  cos_phi /= 2 * a * b;
  cos_phi = min(max(-1.0, cos_phi), 1.0);
  double phi = acos(cos_phi);
  return phi;
}

double angle(const Point &A, const Point &B, const Point &C) {
  double c = dist(A, B);
  double b = dist(A, C);
  double a = dist(C, B);
  return angle(c, a, b);
}

int doit(vector<Point> &points, int i, int j) {
  debug(i);
  debug(j);
  int n = points.size();
  int j_1 = (j + 1) % n;
  Point Ai = points[i];
  Point Bj = points[j];
  Point Cj_1 = points[j_1];

  double phi = angle(Bj, Ai, Cj_1);
  debug(angle(points[j], points[i], points[j_1]));
  make_rotation(points, i, j, phi);
  debug(angle(points[j], points[i], points[j_1]));
  int sign = +1;
  if (fabs(angle(points[j], points[i], points[j_1])) > 1e-6) {
    sign = -1;
    make_rotation(points, i, j, -2.0 * phi);
    debug(angle(points[j], points[i], points[j_1]));
  }

  double a = dist(Ai, Bj);
  double b = dist(Ai, Cj_1);

  int pi = (i + n - 1) % n;
  int ni = (i + 1) % n;
  double anglesSum = angle(points[ni], points[i], points[j]) +
                     angle(points[pi], points[i], points[j_1]);
  double phi2 = angle(a, b, 1);
  int ret = 1;
  if (phi2 > PI - 1e-4 - anglesSum) {
    phi2 = PI - 1e-4 - anglesSum;
    ret = 2;
  }
  // phi2 = min(phi2, PI - 1e-3 - anglesSum);

  make_rotation(points, i, j, -sign * phi2);

  debug(dist(points[j], points[j_1]));

  /*if (fabs(1.0 - dist(points[j], points[j_1])) > 1e-8) {
      make_rotation(points, i, j, 2.0*sign*phi2);
  }*/
  /*if (fabs(1.0 - dist(points[j], points[j_1])) > 1e-8) {
      return 0;
      //fail = 1;
  }*/
  /*if ((angle(points[j], points[i], points[j_1])) >= PI)
      return 0;*/
  return ret;
}

void doall(vector<Point> &points) {
  for (int kk = 0; kk < 20; ++kk) {
    for (int j = 0; j < points.size(); ++j) {
      int j_1 = (j + 1) % points.size();
      int i = j;
      int it = 0;
      while (it < 30) {
        while (i == j || i == j_1) {
          i = rand() % points.size();
        }
        vector<Point> pp(points);
        int ret;
        if ((ret = doit(pp, i, j)) != 0) {
          points = pp;
          if (ret == 1) {
            break;
          }
        }
        ++it;
      }
      /*if (it > 95)
          fail = 1;*/
      // debug(test(points));
    }
  }
}

bool test(const vector<Point> &points) {
  auto d = distances(points);
  debug(d);
  if (fabs(1.0 - *min_element(all(d))) > 1e-8) {
    return true;
  }
  if (fabs(1.0 - *max_element(all(d))) > 1e-8) {
    return false;
  }

  int n = points.size();
  vector<double> a;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    int k = (j + 1) % n;
    // debug(angle(points[i], points[j], points[k]));
    if (angle(points[i], points[j], points[k]) <= 1e-4) {
      return false;
    }
    if (angle(points[i], points[j], points[k]) >= PI - 1e-4) {
      return false;
    }
    a.push_back(angle(points[i], points[j], points[k]));
  }
  sort(all(a));
  debug(a);
  double anglesSum = accumulate(all(a), 0.0);
  if (fabs(anglesSum - PI * (points.size() - 2)) > 1e-3) {
    return false;
  }
  for (int i = 0; i + 1 < a.size(); ++i) {
    if (fabs(a[i] - a[i + 1]) < 1e-4) {
      return false;
    }
  }
  return true;
}

int main() {

  int n;
  cin >> n;

  int it = 0;
  while (true) {
    fail = false;
    vector<Point> p = generateInitPoints(n);
    p = homot(p);
    {
      vector<double> d = distances(p);
      debug(d);
    }
    doall(p);
    if (!fail && test(p)) {
      for (int i = 0; i < p.size(); ++i) {
        printf("%0.16lf %0.16lf\n", p[i].real(), p[i].imag());
      }
      return 0;
    }
    std::cerr << "Fail " << it << "\n";
    ++it;
  }

  /*vector<double> d = distances(p);
  debug(d);
  debug(test(p));*/

  return 0;
}
