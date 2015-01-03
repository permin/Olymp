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
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;};

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

ll sqr(int x) {
    return 1LL * x * x;
}

ll gcd(ll a, ll b) {
    while(b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<vi> al(n);
        vi x(n);
        vi y(n);
        vi r(n);
        for (int i = 0 ;i < n; ++i) {
            cin >> x[i] >> y[i] >> r[i];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j)
                    continue;
                if (sqr(x[i] - x[j]) + sqr(y[i] - y[j]) == sqr(r[i] + r[j])) {
                    al[i].push_back(j);
                }
            }
        }
        queue<int> Q;
        Q.push(0);
        vector<ll> p(n);
        vector<ll> q(n);
        vi sign(n);
        vector<bool> used(n);
        used[0] = 1;
        p[0] = 1;
        q[0] = 1;
        sign[0] = 1;
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int v2: al[v]) {
                if (!used[v2]) {
                    Q.push(v2);
                    used[v2] = 1;
                    ll A = r[v] * p[v];
                    ll B = r[v2] * q[v];
                    ll d = gcd(A, B);
                    p[v2] = A / d;
                    q[v2] = B / d;
                    sign[v2] = -sign[v];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (sign[i] == 0) {
                cout << "not moving\n";
            } else {
                cout << p[i];
                if (q[i] != 1)
                cout << "/" << q[i];
                if (sign[i] == 1) {
                    cout << " clockwise\n";
                } else {
                    cout << " counterclockwise\n";
                }
            }
        }
    }
    return 0;
}
