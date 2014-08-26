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

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    for (int i = 0; i < 3 && i < n; ++i) {
        for (int j = 0; j < 3 && j < m; ++j) {
            for (int x = 0; x < 3 && x < n; ++x) {
                for (int y = 0; y < 3 && y < m; ++y) {
                    for (int p = 0; p < 3 && p < n; ++p) {
                        for (int q = 0; q < 3 && q < m; ++q) {
                            set<pii> a;
                            set<int> c;
                            set<int> r;
                            a.insert(pii(i,j));
                            a.insert(pii(x,y));
                            a.insert(pii(p,q));

                            c.insert(i);
                            c.insert(x);
                            c.insert(p);

                            r.insert(j);
                            r.insert(y);
                            r.insert(q);

                            if (a.size() != 3)
                                continue;
                            ll cur = 1LL * m * c.size() + 1LL * n * r.size() - 1LL * c.size() * r.size() - 3;
                            if (cur == k) {
                                cout << i + 1 << " " << j + 1 << " " << x + 1 << " " << y + 1 << " " << p + 1 << " " << q + 1 << "\n";
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main() {
    int t;
    cin >> t;
    while( t-->0) {
        solve();
    }
    return 0;
}

