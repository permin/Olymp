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
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL_((0,__VA_ARGS__, 5,4,3,2,1))
#define VA_NUM_ARGS_IMPL_(tuple) VA_NUM_ARGS_IMPL tuple
#define VA_NUM_ARGS_IMPL(_0,_1,_2,_3,_4,_5,N,...) N

#define macro_dispatcher(macro, ...) macro_dispatcher_(macro, VA_NUM_ARGS(__VA_ARGS__))
#define macro_dispatcher_(macro, nargs) macro_dispatcher__(macro, nargs)
#define macro_dispatcher__(macro, nargs) macro_dispatcher___(macro, nargs)
#define macro_dispatcher___(macro, nargs) macro ## nargs

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
    vector<ll> x(n);
    vector<ll> b(n);
    map<ll, ll> sumb;
    map<ll, int> c;
    ll totalSumB = 0;
    for (int i = 0; i < n; ++i) {
        int y;
        cin >> x[i] >> y;
        x[i] *= 100; x[i] += y;
        cin >> b[i];
        b[i] *= 100;
        sumb[x[i]] += b[i];
        totalSumB += b[i];
        c[x[i]] += 1;
    }
    ll mb = *min_element(all(b));
    set<ll> es(all(x));
    es.insert(0);
    es.insert(mb);
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += b[i] - x[i];
    }
    ll res = sum;
    ll prev = 0;
    for (ll v: es) {
        if (v == mb)
            break;
        if (v == 0)
            continue;
        sum += 1LL * (n) * (v - prev);
        sum -= 1LL * sumb[v];
        res = min(res, sum);
        prev = v;
    }
    cout << res << "\n";
    return 0;
}

