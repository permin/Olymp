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

int main() {

    int n;
    cin >> n;
    vector<int> deg(n);
    for (int i = 0; i < n - 1; ++i) {
        int a,b;
        cin >> a >> b;
        ++deg[a - 1];
        ++deg[b - 1];
    }
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }
    int one = std::count(all(deg), 1);
    int two = std::count(all(deg), 2);
    int three = std::count(all(deg), 3);
    if (one + two + three != n) {
        cout << "-1\n";
        return 0;
    }
    if (n == 2) {
        cout << 2 << "\n";
        return 0;
    }
    assert(two + three > 0);
    int res = INF;
    if (two) {
        res = min(res, 1 + (two-1) * 2 + three);
    }
    if (three) {
        res = min(res, 3 + two * 2 + (three - 1));
    }
    cout << res << "\n";
    return 0;
}

