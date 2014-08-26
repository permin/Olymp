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

vector<vector<pii> > gen(int n) {
    vector<vector<pii> > r(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            int k2 = i * i - j * j;
            double kd = sqrt(1.0 * k2);
             for (int d = -2; d <= +2; ++d) {
                int k = kd + d;
                if (k >= 0 && k * k + j * j == i * i)
                    r[i].push_back(pii(j, k));
            }
        }
    }
    return r;
}

bool collinear(int x, int y, int a, int b) {
    return x * b - y * a == 0;
}

bool tr(int L, const vector<vector<pii>>& pt, double* res) {
    vector<int> interesing;
    for (int i = 0; i < pt.size(); ++i) {
        if (pt[i].empty())
            continue;
        else
            interesing.push_back(i);
    }
    //debug(interesing);
    bool ok = 0;
    for (int i = 0; i < interesing.size(); ++i) {
        int a = interesing[i];
        if (a > L)
            break;
        for (int j = i; j < interesing.size(); ++j) {
            int b = interesing[j];
            if (a + b > L)
                break;
            for (int x = 0; x < pt[a].size(); ++x)
                for (int y = 0; y < pt[b].size(); ++y) {
                    for (int sign = -1; sign <= +1; sign += 2) {
                        for (int sign2 = -1; sign2 <= +1; sign2 += 2) {
                            int xx = pt[a][x].first + sign2 * pt[b][y].first;
                            int yy = pt[a][x].second + sign * pt[b][y].second;
                            int c = L - a - b;
                            if (a == 5 && b == 10) {
                            }
                            //if (collinear(xx,yy, pt[a][x].first ,pt[a][x].second))
                            //    continue;
                            if (xx * xx + yy * yy == c * c) {
                                *res =min(*res, max<double>(a,max<double>(b,c))-min<double>(a,min<double>(b,c)));
                                ok = 1;
                            }
                        }
                    }
                }
        }
    }

    for (int a = 1; a < L; ++a)
        for (int b = 1; b + a < L; ++b) {
            int c = L - a - b;
            if (a * a + b * b == c * c) {
                *res =min(*res, max<double>(a,max<double>(b,c))-min<double>(a,min<double>(b,c)));
                ok = 1;
            }
        }

    return ok;
}

double re(int L) {
    if (L < 4)
        return -1.0;
    return (L/2)&1;
}

class FindPolygons{
public:
    double minimumPolygon(int L) {
        vector<vector<pii> > pt = gen(L + 1);
        if (L % 2)
            return -1.0;
        double res = 1e9;
        if (tr(L, pt, &res))
            return res;
        return re(L);
    }
};

int main() {

    debug(FindPolygons().minimumPolygon(32));
    debug(gen(40));
    return 0;
    debug(FindPolygons().minimumPolygon(102));
    /*auto r = gen(5000);
    for (int i = 4; ; ++i) {
        if (r[i].empty())
            continue;
        for (int k = 1; k <= 10; ++k) {
            int LLL = i + k * i;
            LLL += LLL;
            if (FindPolygons().minimumPolygon(LLL) < 0 && (LLL % 2 == 0) && ((LLL/2) % 2) == 1) {
                debug(LLL);
                debug(i);
                debug(k);
                return 0;
            }

        }
    }A*/

    return 0;
    debug(FindPolygons().minimumPolygon(30));
    return 0;
    debug(FindPolygons().minimumPolygon(12));
    debug(FindPolygons().minimumPolygon(4984));
    return 0;
    return 0;
}
