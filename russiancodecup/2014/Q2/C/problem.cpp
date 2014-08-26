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
typedef vector<ll> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

ll s(int n) {
    return 1LL * n * (n+1) /2;
}

void f(int x, int y, vi& a) {
    if (x > y)
        return f(y,x,a);
    if (x == 1) {
        return;
    }
    if (x == 2) {
        a.push_back(y - 2);
        return ;
    }
    if (x > 2) {
        ll firstPart = s(x-2);
        a.push_back(firstPart);
        ll area = 1LL * x * y;
        a.push_back(area - firstPart - x - x + 1 - y + 1);
    }
}

void solve() {
    int n,m,x,y;
    cin >> n >> m >> x >> y;
    --x;
    --y;
    vector<ll> a;
    vector<ll> b;
    f(x+1,y+1,a);
    f(x+1,m-y,a);
    f(n-x,y+1,a);
    f(n-x,m-y,a);
    for (int i = 0;i < a.size(); ++i)
        if (a[i] > 0)
            b.push_back(a[i]);

    cout << b.size() << " ";
    sort(all(b));
    for (int i = 0; i < b.size(); ++i)
        cout << b[i] << " ";
    cout << "\n";
}
int main() {
    int t;
    cin >> t;
    while(t-->0) {
        solve();
    }
    return 0;
}

