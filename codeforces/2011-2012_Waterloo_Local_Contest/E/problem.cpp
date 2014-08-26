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

void solveTest() {
    int c,t,l;
    cin >> c >> t >> l;
    vector<vector<ll>> p(c + 2, vector<ll>(t, 0));
    for (int i = 0; i < t; ++i)
        p.back()[i] = l;
    vector<vector<ll>> e(c + 2, vector<ll>(t, 0));

    for (int i = 0; i < c; ++i)
        for (int j = 0; j < t; ++j)
            cin >> p[i + 1][j] >> e[i + 1][j];

    vector<ll> dpNew(t, LLINF);
    vector<ll> dpOld(t, 0);
    for (int i = c; i >= 0; --i) {
        dpNew.assign(t, LLINF);
        for (int k = 0; k < t; ++k)
            for (int j = 0; j < t; ++j) {
                dpNew[k] = min(dpNew[k], dpOld[j] + e[i][k] + abs(p[i][k] - p[i+1][j]));
            }
        dpNew.swap(dpOld);
    }
    cout << dpOld[0] << "\n";
}

int main() {
    int z;
    cin >> z;
    while (z-->0) {
        solveTest();
    }
    return 0;
}

