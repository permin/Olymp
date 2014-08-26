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

bool enough(double x, double y) {
    return x >= y - 1e-9;
}

void solve(double C, double F, double X) {
    double best = 1e60;
    double sum = 0.0;
    for (int f = 0; f < 10*1000*1000; ++f) {
        //double ob = best;
        if (f == 0)
            best = min(best, X / 2);
        else if (f == 1) {
            best = min(best, C / 2 + X / (F + 2));
            sum += C / 2;
        } else {
            best = min(best, sum + C / (2 + F * (f - 1)) + X / (f * F + 2));
            sum +=  C / (2 + F * (f - 1));
        }
        //if (ob == best) {
        //    break;
        //}
    }
    printf("%0.18lf\n", best);
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        double a,b,c;
        cin >> a>>b>>c;
        cout << "Case #" << i + 1 <<": ";
        solve(a,b,c);
    }
    return 0;
}

