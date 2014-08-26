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

#define debug1(x) cerr << #x << ": "  << (x) << "\n";
#define debug2(x, y) debug1(x); debug1(y);
#define debug3(x, y, z) debug1(x); debug2(y, z);
#define debug4(x, y, z, t) debug1(x); debug3(y, z, t);
#define debug5(x, y, z, t, u) debug1(x); debug4(y, z, t, u);

#define debug(...) macro_dispatcher(debug, __VA_ARGS__)(__VA_ARGS__)
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

int solve(int v, int need, const vii& al, const vi& owner, vii& dp) {
    int &res = dp[need][v];
    if (res >= 0)
        return res;
    if (al[v].empty() && need == 0)
        return res = 1;
    res = 0;
    for (int i = 0; i < al[v].size(); ++i) {
        int v2 = al[v][i];
        if (owner[v2] == owner[v]) {
            if (solve(v2, 1^need, al, owner, dp))
                return res = 1;
        } else {
            if (!solve(v2, need, al, owner, dp))
                return res = 1;
        }
    }
    return res = 0;
}

int main() {
    int tests;
    cin >> tests;
    while(tests --> 0) {
        int n,c,s;
        cin >> n >> c >> s;
        --s;
        vector<int> owner(n);
        for (int i = 0; i < n; ++i)
            cin >> owner[i];
        vii al(n, vi());
        for (int i = 0; i < c; ++i) {
            int a, b;
            cin >> a >> b;
            --a;--b;
            al[a].push_back(b);
        }
        vii dp(2, vi(n, -1));
        if (solve(s, owner[s], al, owner, dp))
            cout <<  owner[s] << "\n";
        else
            cout <<  (1-owner[s]) << "\n";
    }
    return 0;
}

