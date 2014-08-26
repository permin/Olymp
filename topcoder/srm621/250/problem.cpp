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

class RadioRange{
public:
    double sqr(double x) {
        return x*x;
    }
    double dist(double x, double y) {
        return sqrt(sqr(x)+sqr(y));
    }
    void pr(double x, double y, double r, vector<pair<double, int>>& res) {
        if (sqr(x) + sqr(y) < EPS) {
            res.push_back(std::make_pair(0, -1));
            res.push_back(std::make_pair(r, +1));
            return ;
        }
        double len = sqrt(sqr(x)+sqr(y));
        double ex = x / len;
        double ey = y / len;
        double a = x - ex * r;
        double b = y - ey * r;
        double c = x + ex * r;
        double d = y + ey * r;
        double m = dist(a,b);
        double M = dist(c,d);
        if (m > M) {
            swap(m, M);
        }
        if (len > r) {
             res.push_back(std::make_pair(m, -1));
             res.push_back(std::make_pair(M, +1));
        } else {
             res.push_back(std::make_pair(0, -1));
             res.push_back(std::make_pair(M, +1));
        }
    }
    double RadiusProbability(vector <int> X, vector <int> Y, vector <int> R, int Z) {
        vector<pair<double, int>> res;
        for (int i = 0; i < X.size(); ++i) {
            pr(X[i], Y[i], R[i], res);
        }
        res.push_back(make_pair(0,-100));
        res.push_back(make_pair(Z,-100));
        sort(all(res));
        int c = 0;
        double sum = 0;
        bool calc = 0;
        for (int i = 0; i < res.size(); ++i) {
            if (res[i].second == -100) {
                if (res[i].first < 0.5) {
                    calc = 1;
                } else {
                    assert(calc);
                    if (c == 0) {
                        sum += res[i].first - res[i - 1].first;
                    }
                    break;
                }
            } else {
                if (c == 0) {
                    if (calc) {
                        sum += res[i].first - res[i - 1].first;
                    }
                }
                c -= res[i].second;
            }
        }
        return sum / Z;
    }
};

int main() {
    RadioRange A;
    debug(A.RadiusProbability({1},{1},{1},4));
    return 0;
}
