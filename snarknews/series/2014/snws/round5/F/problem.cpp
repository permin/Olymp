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

int solve() {
    int n, m;
    cin >> n >> m;
    vector<string> plan(n);
    bool hasX = 0;
    for (int i = 0; i < n; ++i) {
        cin >> plan[i];
        if (count(all(plan[i]), 'X'))
            hasX = 1;
    }
    if (!hasX)
        return 0;
    int res = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (plan[i][j] != 'X')
                continue;
            int c = 1;
            while (true) {
                bool ok = 1;
                for (int mask = 0; mask < 2 * 2; ++mask) {
                    int cx = i + ((mask & 1) ? +1: -1) * c;
                    int cy = j + ((mask & 2) ? +1: -1) * c;
                    if (cx < 0 || cx >= n || cy < 0 || cy >= m || plan[cx][cy] != 'X')
                        ok = 0;
                }
                if (!ok)
                    break;
                ++c;
            }
            res = max(res, c);
        }
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while(t-->0) {
        cout << solve() << "\n";
    }
    return 0;
}

