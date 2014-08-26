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

const int mod = 1e9+7.4;
int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int neg(int x) {
    if (x)
        x = mod - x;
    return x;
}

int sub(int x, int y) {
    return add(x, neg(y));
}

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

struct Fenwick {
    explicit Fenwick(int n):
        data(n){}
    void inc(int i, int value) {
        while(i < data.size()) {
            data[i] = add(data[i], value);
            i = i | (i + 1);
        }
    }
    int sum(int r) {
        int res = 0;
        while (r >= 0) {
            res = add(res, data[r]);
            r = (r & (r + 1)) - 1;
        }
        return res;
    }
    vector<int> data;
};

vector<int> firstOcc;
vector<int> lastOcc;
vector<int> eulerTour;
vector<int> depth;

void dfs(int v, const vii& childs, int d = 0) {
    depth[v] = d;
    eulerTour.push_back(v);
    for (int v2: childs[v]) {
        dfs(v2, childs, d + 1);
        eulerTour.push_back(v);
    }
    eulerTour.push_back(v);
}

int main() {
    int n;
    cin >> n;

    firstOcc.assign(n, -1);
    lastOcc.assign(n ,-1);
    depth.assign(n, -1);

    vii childs(n);
    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        --x;
        childs[x].push_back(i);
    }
    dfs(0, childs);

    for (int i = 0; i < eulerTour.size(); ++i) {
        int v = eulerTour[i];
        if (firstOcc[v] == -1)
            firstOcc[v] = i;
        lastOcc[v] = i;
    }

    Fenwick yInter(eulerTour.size());
    Fenwick slope(eulerTour.size());

    //debug(eulerTour);
    //debug(firstOcc);
    //debug(lastOcc);

    int q;
    cin >> q;
    while (q --> 0) {
        int t;
        cin >> t;
        if (t == 1) {
            int v,k,x;
            cin >> v >> x >> k;
            --v;
            x = add(x, mul(k, depth[v]));

            yInter.inc(firstOcc[v], x);
            yInter.inc(lastOcc[v], neg(x));

            slope.inc(firstOcc[v], neg(k));
            slope.inc(lastOcc[v], k);

        } else {
            int v;
            cin >> v;
            --v;

            int yI = yInter.sum(firstOcc[v]);
            int sl = slope.sum(firstOcc[v]);
            //debug(yI);
            //debug(sl);

            cout << add(yI, mul(sl, depth[v])) << "\n";
        }
    }

    return 0;
}

