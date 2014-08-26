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
typedef pair<int, ll> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

void dfs(int v, long long dep, vector<ll>& depth, const vector<vector<pii>>& al) {
    if (depth[v] >= 0)
        return;
    depth[v] = dep;
    for (auto vd: al[v]) {
        dfs(vd.first, dep + vd.second, depth, al);
    }
}

int main() {
    int n;
    cin >> n;
    vector<ll> p(n + 1);
    for (int i = 0; i <= n; ++i)
        cin >> p[i];
    vector<vector<pii>> al(n + 1);
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        int a,b;
        ll c;
        cin >> a >> b >> c;
        res += c;
        res += c;
        al[a].push_back(pii(b,c));
        al[b].push_back(pii(a,c));
    }
    vector<ll> depth(n + 1, -1);
    dfs(0, 0, depth, al);
    ll ec = -INF;
    for (int i = 0; i <= n; ++i) {
        ec = max(ec, depth[i] - p[i]);
    }
    cout << res - ec << "\n";

    return 0;
}

