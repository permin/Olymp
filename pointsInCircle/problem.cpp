#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
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
#include <valarray>
#include <vector>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": " << (x) << "\n";

template <class F, class S>
ostream& operator<<(ostream& o, const pair<F, S>& p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C>
void O__(ostream& o, const C& c) {
  bool f = 1;
  for (const auto& x : c) {
    if (!f) o << ", ";
    f = 0;
    o << x;
  }
}

template <class T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  O__(o, v);
  o << "]";
  return o;
}

template <class T, class V>
ostream& operator<<(ostream& o, const map<T, V>& v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

template <class T>
ostream& operator<<(ostream& o, const set<T>& v) {
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

double sqr(double x) { return x * x; }

struct Point {
  Point(double x, double y) : x(x), y(y) {}
  double x, y;
};

const Point O(0.0, 0.0);

double dist(const Point& A, const Point& B) {
  return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}

std::default_random_engine generator;

Point randomPoint() {
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  Point A(1, 1);
  do {
    A.x = distribution(generator);
    A.y = distribution(generator);
  } while (dist(O, A) > 1.0);
  return A;
}

double det2(double a, double b, double c, double d) { return a * d - b * c; }

double det2(const Point& A, const Point& B) { return det2(A.x, A.y, B.x, B.y); }

double area(const Point& A, const Point& B, const Point& C) {
  return fabs(det2(A, B) - det2(A, C) + det2(B, C));
}

double minH(const Point& A, const Point& B, const Point& C) {
  double h = 1e90;
  h = min(area(A, B, C) / dist(A, B), h);
  h = min(area(A, B, C) / dist(A, C), h);
  h = min(area(A, B, C) / dist(C, B), h);
  return h;
}

double minH(const vector<Point>& ps) {
  double h = 1e90;
  for (int i = 0; i < ps.size(); ++i)
    for (int j = i + 1; j < ps.size(); ++j) {
      for (int k = j + 1; k < ps.size(); ++k)
        h = min(h, minH(ps[i], ps[j], ps[k]));
    }
  return h;
}

vector<Point> genN(int n) {
  vector<Point> res;
  while (n-- > 0) {
    res.push_back(randomPoint());
  }
  return res;
}
int main() {
  int n;
  cin >> n;
  vector<Point> best = genN(n);
  for (int i = 0;; ++i) {
    vector<Point> o(best);
    if (i % (1000) == 0) {
      for (int j = 0; j < n; ++j) o[j] = randomPoint();
    }
    for (int j = 0; j < n; ++j) {
      vector<Point> x(o);
      for (int it = 0; it < 100; ++it) {
        x[j] = randomPoint();
        if (minH(x) > minH(best)) best = x;
      }
    }
    cout << i << " " << minH(best) << endl;
  }

  return 0;
}
