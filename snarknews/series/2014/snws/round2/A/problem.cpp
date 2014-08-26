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
/*
void dfs(int v, vector<bool>& used, vector<int>& dp, const vii& al) {
    if (used[v])
        return ;
    used[v] = 1;
    dp[v] = 0;
    for (int i = 0; i < al[v].size(); ++i) {
        int v2 = al[v][i];
        if (!used[v2]) {
            dfs(v2, used, dp, al);
            dp[v] = max(dp[v], 1 + dp[v2]);
        }
    }
}

void dfs2(int v, vector<bool>& used, map<int, ll>& res, const vii& al, const vi& dp) {
    if (used[v])
        return;
    used[v] = 1;
    vector<int> a;
    for (int i = 0; i < al[v].size(); ++i) {
        int v2 = al[v][i];
        if (!used[v2]) {
            a.push_back(dp[v2]);
        }
    }
    if (a.size() >= 2) {
        sort(a.rbegin(), a.rend());
        if (a[0] == a[1]) {
            int sum = a[0] + a[1];
            int num = count(all(a), a[0]);
            res[sum] += 1LL * num * (num - 1) / 2;

        } else {
            int sum = a[0] + a[1];
            int num = count(all(a), a[1]);
            res[sum] += num;
        }
    }

    for (int i = 0; i < al[v].size(); ++i) {
        int v2 = al[v][i];
        dfs2(v2, used, res, al, dp);
    }
}*/

map<int, ll> res;

vector<int> depth;

void dfs(int v, const vii& al, int p = -1, int d = 0) {
    depth[v] = d;
    for (int v2: al[v]) {
        if (p == v2)
            continue;
        dfs(v2, al, v, d + 1);
    }
}

template<class A, class B>
void merge(map<A, B> &a, map<A, B> & b, map<A, B>& res) {
    if (a.size() < b.size())
        a.swap(b);
    for (auto x: b) {
        a[x.first] += x.second;
    }
    res.swap(a);
}

void solve(int v, map<int, int>& stat, const vii& al, int p = -1) {
    bool leaf = 1;
    vector<pii> a;
    for (int v2: al[v]) {
        if (v2 == p)
            continue;
        leaf = 0;
        map<int, int> stat2;
        solve(v2, stat2, al, v);
        if (!stat2.empty())
            a.push_back(*stat2.rbegin());
        merge(stat2, stat, stat);
    }
    if (leaf)
        stat[depth[v]] += 1;
    if (stat.empty() || a.empty())
        return;
    sort(a.rbegin(), a.rend());
    //debug(v, a);
    /*if (a.rbegin()->second >= 2) {
        int sum = a.rbegin()->first * 2 - 2 * depth[v] + 1;
        ll num = 1LL * a.rbegin()->second;
        num = num * (num - 1) / 2;
        res[sum] += num;
    } else {
        if (a.size() >= 2) {
            auto it= std::next(a.rbegin());
            int sum = a.rbegin()->first + it->first - 2 * depth[v] + 1;
            ll num = it->second;
            res[sum] += num;
        } else {
            int sum = a.rbegin()->first - depth[v] + 1;
            ll num = 1;
            res[sum] += num;
        }
    }*/
    vector<int> x, y;
    for (int i = 0; i < a.size(); ++i) {
        x.push_back(a[i].first);
        y.push_back(a[i].second);
    }
    if (x.size() == 1) {
        int sum = x[0] - depth[v] + 1;
        ll num = y[0];
        res[sum] += num;
    } else {
        if (x[0] == x[1]) {
            int sum = 2 * (x[0] - depth[v]) + 1;
            ll num = 0;
            ll x2 = 0;
            for (int j = 0; j < x.size(); ++j)
                if (x[j] == x[0]) {
                    num += y[j];
                    x2 += 1LL * y[j] * y[j];
                }
            res[sum] += (num * num - x2) / 2;
        } else {
            int sum = x[1] + x[0] - 2*depth[v] + 1;
            ll num = 0;
            for (int j = 0; j < x.size(); ++j)
                if (x[j] == x[1]) {
                    num += y[j];
                }
            res[sum] += num * y[0];
        }
    }

    /*
    if (stat.rbegin()->second >= 2) {
        int sum = stat.rbegin()->first * 2 - 2 * depth[v] + 1;
        ll num = 1LL * stat.rbegin()->second;
        num = num * (num - 1) / 2;
        res[sum] += num;
    } else {
        assert(stat.rbegin()->second == 1);
        auto it = std::next(stat.rbegin());
        if (it != stat.rend()) {
            int sum = stat.rbegin()->first + it->first - 2 * depth[v] + 1;
            ll num = it->second;
            res[sum] += num;
        } else {
            int sum = stat.rbegin()->first - depth[v] + 1;
            ll num = 1;
            res[sum] += num;
        }
    }*/
}

int main() {
    int n;
    cin >> n;
    vector<vector<int> > al(n);
    for (int i = 0; i  +1 < n; ++i) {
        int a,b;
        cin >> a >> b;
        --a;--b;
        al[a].push_back(b);
        al[b].push_back(a);
    }
    depth.resize(n);
    dfs(0, al);
    //debug(depth, 1);
    {
        map<int, int> stat;
        solve(0, stat, al);
        cout << res.rbegin()->first << " " <<  res.rbegin()->second << "\n";
    }
    /*vector<int> dp(n, -1);
    {
        vector<bool> used(n, 0);
        dfs(0, used, dp, al);
    }
    {
        map<int, ll> res;
        vector<bool> used(n, 0);
        dfs2(0, used, res, al, dp);
    }*/
    return 0;
}

