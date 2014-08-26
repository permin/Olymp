#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fstream>
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

struct P {
    double x,y;
    int id;
};

bool operator<(const P& A, const P& B) {
    return make_pair(A.x, A.y) < make_pair(B.x, B.y);
}

double sqr(double x) {
    return x * x;
}

double dist(const P& A, const P& B) {
    return sqr(A.x-B.x) + sqr(A.y-B.y);
}

vector<int> sf(const P& O, int k, const vector<P>& ps) {
    set<pair<double, P> > q;
    for (const P& c: ps) {
        q.insert(make_pair(dist(c, O), c));
        if (q.size() > k)
            q.erase(std::prev(q.end()));
    }
    vi r;
    for (auto x: q) {
        r.push_back(x.second.id);
    }
    return r;
}

vi s1(const P& O, int K, const vector<P>& ps) {
    vector<P> xO, yO;
    xO = yO = ps;
    auto compareX = [&](const P& p1, const P& p2) {
                return p1.x < p2.x;
            };
    auto compareY = [&](const P& p1, const P& p2) {
                return p1.y < p2.y;
            };
    sort(all(xO), compareX);
    sort(all(yO), compareY);
    int i = std::distance(xO.begin(), std::lower_bound(all(xO), O, compareX));
    int j = std::distance(yO.begin(), std::lower_bound(all(yO), O, compareY));
    debug(i);
    debug(j);
    int C = 1000;
    set<pair<double, P> > q;
    for (int k = -C; k <= +C; ++k) {
        if (i + k >= 0 && i + k < ps.size()) {
            const P& c = xO[i];
            q.insert(make_pair(dist(c, O), c));
            if (q.size() > K)
                q.erase(std::prev(q.end()));
        }
        if (j + k >= 0 && j + k < ps.size()) {
            const P& c = yO[j];
            q.insert(make_pair(dist(c, O), c));
            if (q.size() > K)
                q.erase(std::prev(q.end()));
        }
    }
    vi r;
    for (auto x: q) {
        r.push_back(x.second.id);
    }
    return r;
}

void read(vector<P>& ps) {
    double x,y;
    int i;
    ifstream fin("./1M_points");
    while(fin >> x >> y >> i) {
        ps.push_back({x,y,i});
    }
}

int main() {
    vector<P> ps;
    read(ps);
    double x,y;
    int k;
    while (cin >> x >> y >> k) {
        debug(sf({x,y,-1}, k, ps));
        debug(s1({x,y,-1}, k, ps));
    }
    return 0;
}

