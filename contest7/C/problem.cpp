/* Team: moscow04 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <deque>
#include <queue>
#include <string>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>

#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

#define DEBUG

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)((a).size()))
#define pb push_back
#define MP make_pair
#define mp MP

#ifdef DEBUG
    #define debug(x) cerr << #x << ": " << (x) << endl;
#else
    #define debug(x) ;
#endif

typedef pair<int, int> pii;
typedef long long ll;

template <typename T> T sqr (T x) {return x * x;}
template <typename T> T abs (T x) {return x > 0 ? x : -x;}

template <typename T>
ostream & operator << (ostream & out, vector<T> const & a) {
    out << "[";
    for (int i = 0; i < sz(a); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << a[i];
    }
    out << "]";
    return out;
}

template <typename T1, typename T2>
ostream & operator << (ostream & out, pair<T1, T2> const & p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

void showTime () {
#ifdef DEBUG
    static double prev;
    static bool first = true;

    double curr = (double)clock() / CLOCKS_PER_SEC;

    cerr.setf(ios::fixed);
    cerr.precision(3);
    cerr << "<";
    if (!first) {
        cerr << curr - prev << "sec, ";
    }
    cerr << curr << "sec>\n";

    first = false;
    prev = curr;
#endif
}

const int N = 2e3 + 10;
int a[N];
int n, k, m;

void gen () {
    n = 2e3;
    k = 2e5;
    m = 1e9;

    for (int i = 0; i < n; ++i) {
        a[i] = rand() % (int)1e9;
    }
}

int calc (int x) {
    unsigned long long e = 0;
    unsigned long long bound = x ? std::numeric_limits<unsigned long long>::max() / x : 10000;
    for (int i = n - 1; i >= 0; --i) {
        e *= x;
        e += a[i];
        if (e >= bound) //(1ULL << (63-17)))
           e %= m;
    }

    return e % m;
}


void read () {
    scanf("%d%d%d", &n, &k, &m);
    //cin >> n >> k >> m;
    for (int i = 0; i < n; ++i) {
        //cin >> a[i];
        scanf("%d", &a[i]);
    }
}

int main () {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // gen();
    read();

    for (int i = 0; i <= k; ++i) {
        printf("%d ", calc(i));
    }

    // showTime();
    return 0;
}
