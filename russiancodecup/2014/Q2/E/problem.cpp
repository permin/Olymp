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

struct Edge {
    int source, target, lower, upper;
    ll mul;
};

void dfs(int v, int p, vi& s, vector<vector<Edge>>& edges) {
    assert(s[v] == 0);
    s[v] = 1;
    for (int i = 0; i < edges[v].size(); ++i) {
        assert(edges[v][i].source == v);
        int v2 = edges[v][i].target;
        if (v2 == p)
            continue;
        dfs(v2, v, s, edges);
        edges[v][i].mul = 1LL * (edges.size() - s[v2]) * s[v2];
        s[v] += s[v2];
    }
}

int add(int x, int y) {
    const int mod = 1e9 + 7;
    int r = x + y;
    if (r >= mod)
        r -= mod;
    return r;
}

int sub(int x, int y) {
    const int mod = 1e9 + 7;
    if (y == 0)
        return x;
    return add(x, mod - y);
}

void pr(const vector<int>& dp) {
    cerr << "{\n";
    for (int i = 0; i < dp.size(); ++i) {
        if (dp[i]) {
            cerr << "\t" << i << ": " << dp[i] << "\n";
        }
    }
    cerr << "}\n";
}

int dp[255555];
int dpNew[255555];
char calc[255555];

int main() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    if (m & 1) {
        cout << 0;
        return 0;
    }
    m/=2;
    vector<vector<Edge>> al(n);
    for (int i = 0; i +1 < n; ++i) {
        int x,y,z,t;
        cin >> x >> y >> z >> t;
        --x;--y;
        al[x].push_back({x,y,z,t,-1});
        al[y].push_back({y,x,z,t,-1});
    }
    vector<ll> s(n, 0);
    dfs(0, -1, s, al);

    vector<ll> lower;
    vector<ll> upper;
    vector<ll> mul;
    for (int i = 0; i < al.size(); ++i) {
        for (int j = 0; j < al[i].size(); ++j) {
            if (al[i][j].mul >= 0) {
                lower.push_back(al[i][j].lower);
                upper.push_back(al[i][j].upper);
                mul.push_back(al[i][j].mul);
            }
        }
    }
    debug(lower);
    debug(upper);
    debug(mul);
    assert(lower.size() == n - 1);
    {
        ll sum = 0;
        for (int i = 0; i < lower.size(); ++i) {
            sum += 1LL * lower[i] * mul[i];
        }
        if (sum > m) {
            cout << "0\n";
            return 0;
        }
    }
    debug(n);


    //vector<int> dp(m + 1, 0);
    dp[m] = 1;

    //pr(dp);

    int it = 0;
    int CC = 1e6 * 500;
    for (int i = n - 2; i >= 0; --i) {
        //vector<int> dpNew(dp.size());
        memset(dpNew, 0, sizeof(int) * (m+1));
        memset(calc, 0, sizeof(char) * (m+1));
        //vector<bool> calc(m + 1);
        for (int s = 0; s <= m; ++s) {
            if (calc[s])
                continue;
            int sum = 0;
            ll x,y;
            x = y = lower[i] * mul[i] ;
            for (int v = lower[i]; v <= upper[i] && 1LL * s + 1LL * x < (m+1); x += mul[i], ++v) {
                sum = add(sum, dp[s + x]);
                ++it;
                assert(it < CC);
            }
            x+=s;
            y+=s;
            ll s_ = s;
            while (s_ <= m) {
                ++it;
                calc[s_] = 1;
                dpNew[s_] = sum;
                if (x < (m+1)) {
                    sum = add(sum, dp[x]);
                    x += mul[i];
                }
                if (y < (m+1)) {
                    sum = sub(sum, dp[y]);
                    y += mul[i];
                }

                s_ += mul[i];
                assert(it < CC);
            }
            assert(it < CC);
        }
        assert(it < CC);
        //dp.swap(dpNew);
        memcpy(dp, dpNew, sizeof(int) * (m+1));
        //pr(dp);
    }
    debug(it);
    cout << dp[0] << "\n";


    return 0;
}

