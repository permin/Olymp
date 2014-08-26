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
bool f = 1; for(const auto& x: c) {if (!f) o << "\n "; f = 0; o << x;}}

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

int main() {
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int s = accumulate(all(a), 0);
    vector<string> p(s + s + 10, string(s + s + 10, ' '));
    int x = s + 5;
    int y = 0;
    for (int i = 0; i < n; ++i) {
        while(a[i]-->0) {
            p[x][y] = (i&1)? '\\': '/';
            ++y;
            if (a[i])
                x += ((i&1)? +1: -1);
        }
    }
    int mx= INF;
    int my = INF;
    int Mx = 0;
    int My = 0;
    for (int i = 0; i < p.size(); ++i) {
        for (int j =0 ; j < p[i].size(); ++j) {
            if (p[i][j] != ' ') {
                mx = min(mx, i);
                my = min(my, j);
                Mx = max(Mx, i);
                My = max(My, j);
            }
        }
    }
    for (int i = mx; i <= Mx; ++i) {
        for (int j = my; j <= My; ++j) {
            cout << p[i][j];
        }
        cout << "\n";
    }
    return 0;
}

