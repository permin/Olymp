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

const int N = 100;
double am[N][N];

double sqr(double x) {
    return x * x;
}

double score(const vi& p) {
    double r = 0;
    for (int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        r += am[p[i]][p[j]];
    }
    return r;
}

vi solve(vi p) {
    while (true) {
        int bi, bl;
        bi = -1;
        bl = -1;
        double win = 0.0;
        for (int i = 0; i < p.size(); ++i) {
            for (int le = 2; le + 1 < p.size(); ++le) {
                int pi = i - 1;
                if (pi < 0)
                    pi = p.size() - 1;
                int j = (i + le - 1);
                if (j >= p.size())
                    j -= p.size();
                int nj = j + 1;
                if (nj == p.size())
                    nj = 0;
                double w = am[p[pi]][p[i]] + am[p[j]][p[nj]] - am[p[pi]][p[j]] - am[p[i]][p[nj]];
                if (w > win) {
                    win = w;
                    bi = i;
                    bl = le;
                }
            }
        }
        if (win < EPS) {
            return p;
        }
        int i = bi;
        int j = bi + bl - 1;
        if (j >= p.size())
            j -= p.size();
        for (int e = 0; e < bl/2; ++e) {
            swap(p[i], p[j]);
            ++i;
            --j;
            if (i == p.size())
                i = 0;
            if (j == -1)
                j = p.size() - 1;
        }
    }
}

class DSU  {
public:
    DSU(int n) {
        for (int i = 0; i < n; ++i)
            par.push_back(i);
    }
    void merge(int x, int y) {
        x = getPar(x);
        y = getPar(y);
        par[x] = y;
    }
    int getPar(int x) {
        return x == par[x] ? x : par[x] = getPar(par[x]);
    }
private:
    vi par;
};

void dfs(int v, const vii& al, vi& o, int p = -1) {
    o.push_back(v);
    for (int v2: al[v]) {
        if (v2 == p)
            continue;
        dfs(v2, al, o, v);
    }
}

int main() {
    int n;
    cin >> n;
    vector<double> x(n);
    vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<pair<double, pii>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            am[i][j] = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
            edges.push_back(MP(am[i][j], pii(i,j)));
        }
    }

    double best = INF;
    vi bestPerm = {};
    int it = 0;
    while(1) {
        ++it;
        DSU dsu(n);
        sort(all(edges));
        vii al(n);
        vi c(n, 0);
        for (int k = 0; k <edges.size(); ++k) {
            if (k + 50 < edges.size() && rand() % 2 != 3) {
                std::random_shuffle(edges.begin() + k, edges.begin() + k + 50);
            }
            auto e = edges[k];
            int i = e.second.first;
            int j = e.second.second;
            if (dsu.getPar(i) == dsu.getPar(j))
                continue;
            c[i]++;
            c[j]++;
            dsu.merge(i, j);
            al[i].push_back(j);
            al[j].push_back(i);
        }

        vi perm;
        dfs(rand() % n, al, perm);
        if (perm.size() != n)
            continue;
        perm = solve(perm);
        if (best > score(perm)) {
            best = score(perm);
            bestPerm = perm;
            debug(best);
            debug(it);
        }
    }
    printf("%0.18lf\n", best);
    debug(bestPerm);
    return 0;
}
