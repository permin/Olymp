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
const int INF = std::numeric_limits<int>::max() / 2;
const long long LLINF = std::numeric_limits<ll>::max();

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vii am(n, vi(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> am[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (am[i][j] != am[j][i] || am[i][i] > 0) {
                cout << "NO\n";
                return 0;
            }
        }
    }

    vector<pii> ord;
    for (int i = 0; i < n; ++i) {
        ord.push_back(pii(am[0][i], i));
    }
    sort(all(ord));
    vii d(n, vi(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = am[ord[i].second][ord[j].second];
        }
    }
    am = d;
    vector<vector<pii>> al(n);
    for (int i = 1; i < n; ++i) {
        int mi = INF;
        int pm = -1;
        for (int p = 0; p < i; ++p) {
            if (am[i][p] < mi) {
                mi = am[i][p];
                pm = p;
            }
        }
        if (mi == 0 || mi == INF) {
            cout << "NO\n";
            return 0;
        }
        al[pm].push_back(pii(i, mi));
        al[i].push_back(pii(pm, mi));
        set<pii> Q;
        Q.insert(pii(0,i));
        vi dist(i + 1, INF);
        dist[i] = 0;
        while(!Q.empty()) {
            int v = Q.begin()->second;
            Q.erase(Q.begin());
            for (const auto& e: al[v]) {
                int v2 = e.first;
                if (dist[v2] > dist[v] + e.second) {
                    Q.erase(pii(dist[v2], v2));
                    dist[v2] = dist[v] + e.second;
                    Q.insert(pii(dist[v2], v2));
                }
            }
        }
        for (int v= 0; v <= i; ++v) {
            if (am[v][i] != dist[v]) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    return 0;
}
