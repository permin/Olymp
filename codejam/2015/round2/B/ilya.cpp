#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<sstream>
#include<utility>
#include<map>
#include<ctime>
#include<cstdio>
#include<cassert>
#include<functional>




using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<char, char> pcc;
typedef pair<double, double> pdd;
typedef pair<ll, double> pid;

#define show(x) cerr << x
#define debug(x) show(#x << ": " << (x) << endl)

const long double PI = 3.14159265358979323846;
const long double gammama = 0.57721566490153286060;
const long double eps = 1e-9;
const int INF = 1000 * 1000 * 1000 + 1;
const ll LINF = (ll)1000 * 1000 * 1000 * 1000 * 1000 * 1000;
const ll mod = 1000 * 1000 * 1000 + 7;
const ll N = 1001;
//const int M = 10000000;



double solve() {
    int n;
    double v, xd;
    cin >> n >> v >> xd;
    ll x = xd * 10000 + 0.5;
    vector<pid> t(n);
    bool ok1 = false, ok2 = false;
    for (int i = 0; i < n; ++i) {
        double td;
        cin >> t[i].second >> td;
        t[i].first = td * 10000 + 0.5;
        if (t[i].first >= x)
            ok1 = 1;
        if (t[i].first <= x)
            ok2 = 1;
    }
    if ((!ok1) || (!ok2))
        return -1.;
    sort(t.begin(), t.end());
    if (x == t[0].first) {
        int j = 0;
        while ((j < n) && (t[j].first == x))
            ++j;
        double rate = 0;
        for (int i = 0; i < j; ++i)
            rate += t[i].second;
        return v / rate;
    }
    if (x == t[n - 1].first) {
        int j = n - 1;
        while ((j >= 0) && (t[j].first == x))
            --j;
        double rate = 0;
        for (int i = n - 1; i > j; --i)
            rate += t[i].second;
        return v / rate;
    }
    double low = 0, up = v * 10000 + 100;
    for (int it = 0; it < 100; ++it) {
        double mid = (up + low) / 2;
        double cv = 0;
        double ct = 0;
        for (int i = 0; i < n; ++i) {
            double bound = min(t[i].second * mid, v - cv);
            cv += bound;
            ct += bound * t[i].first;
        }
        double mini = ct;
        bool ok = 1;
        if (cv + eps < v)
            ok = false;
        ct = cv = 0;
        for (int i = n - 1; i >= 0; --i) {
            double bound = min(t[i].second * mid, v - cv);
            cv += bound;
            ct += bound * t[i].first;
        }
        if (cv + eps < v)
            ok = false;
        if ((mini <= v * x) && (v * x <= ct) && ok)
            up = mid;
        else
            low = mid;
    }
    return up;

}


void solveAns() {
    double res = solve();

    if (res < 0)
        cout << "IMPOSSIBLE" << endl;
    else
        printf("%0.18f\n", res);
}


int main() {
    int tt;

    cin >> tt;
    for (int i = 0; i < tt; ++i) {
        cout << "Case #" << i + 1 << ": ";
        solveAns();

        std::cerr << i << endl;
    }
    return 0;
}

