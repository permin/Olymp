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



void  solveTest() {
    int n,a,b;
    cin >> n >> a >> b;
    bool bad = 0;
    if (a > b)
        bad = 1;
    if (a >= n || b >= n)
        bad = 1;
    if (a == 0 && b != 0)
        bad = 1;
    if (a != 0 && b == 0)
        bad = 1;
    if (bad) {
        cout << "IMPOSSIBLE\n" ;
        return;
    }
    int diff = b - a;
    for (int i = 0; i + 1 < a; ++i) {
        cout << "1 " << i + 2 << "\n";
    }
    if (a > 0) {
        cout << (1 + diff) << " ";
        for (int i = 0; i < 1 + diff; ++i) {
            cout << a + 1 + i << " ";
        }
        cout << "\n";
    }
    for (int i = a; i < n; ++i)
        cout << "0\n";
}

int main() {
    int t;
    cin >> t;
    while(t-->0) {
        solveTest();
    }
    return 0;
}

