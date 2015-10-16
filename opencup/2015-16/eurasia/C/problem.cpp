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
const int INF = 2 * 1000 * 1000 * 1000;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

void NO() {
    cout << "NO\n";
    exit(0);
}

enum Type {Less, LessOrEqual};


// x </<= y
// x + gap <= y
int gap(Type t) {
    if (t == Less)
        return 1;
    return 0;
}

void dfs(int v, vector<bool>& used, const vector<vector<pair<Type, int>>>& al, vi& order) {
    if (used[v])
        return;
    used[v] = 1;
    for (auto tv2: al[v]) {
        dfs(tv2.second, used, al, order);
    }
    order.push_back(v);
}

void dfs2(int v, int c, vi& compId, const vii& tr) {
    if (compId[v] >= 0) {
        //assert(compId[v] == c);
        return;
    }
    compId[v] = c;
    for (int v2: tr[v]) {
        dfs2(v2, c, compId, tr);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n,k;
    cin >> n >> k;
    swap(n,k);

    vector<vector<pair<Type, int>>> al(n);
    vi minValue(n, -INF);
    vi maxValue(n, +INF);

    for (int i = 0; i < k; ++i) {
        int x,y,z,p, q;
        cin >> x >> y >> z >> p >> q;
        Type t = (x == 0 ? LessOrEqual: Less);
        if (y == 0 && p == 0) {
            al[z-1].emplace_back(t, q-1);
        } else if (y == 0 && p == 1) {
            // x <= 3
            maxValue[z-1] = min(maxValue[z-1], q - gap(t));
        } else if (y == 1 && p == 0) {
            // 3 <= x
            minValue[q-1] = max(minValue[q-1], z + gap(t));
        } else if (y == 1 && p == 1) {
            // 3 <= 41
            if (!(z + gap(t) <= q)) {
                NO();
            }
        }
    }

    debug(minValue);
    debug(maxValue);

    {
        vi order;
        vector<bool> used(n);
        for (int i = 0; i < n; ++i) {
            if (!used[i])
                dfs(i, used, al, order);
        }
        reverse(all(order));
        debug(order);
        vii tr(n);
        for (int i = 0; i < n; ++i) {
            for (const auto& tv2: al[i]) {
                tr[tv2.second].push_back(i);
            }
        }
        debug(tr);

        vector<int> compId(n, -1);
        int c = 0;

        for (int v: order) {
            if (compId[v] == -1) {
                dfs2(v, c, compId, tr);
                ++c;
            }
        }

        vector<vector<pair<Type, int>>> condencedGraph(c);
        vi minValueCondenced(n, -INF);
        vi maxValueCondenced(n, INF);
        for (int i = 0; i < n; ++i) {
            minValueCondenced[compId[i]] = max(minValueCondenced[compId[i]],
                    minValue[i]);
            maxValueCondenced[compId[i]] = min(maxValueCondenced[compId[i]],
                    maxValue[i]);
        }
        debug(compId);
        for (int i = 0; i < n; ++i) {
            for (const auto& tv2: al[i]) {
                if (compId[i] == compId[tv2.second]) {
                    if (tv2.first != LessOrEqual) {
                        NO();
                    }
                }
                condencedGraph[compId[i]].emplace_back(tv2.first, compId[tv2.second]);
            }
        }

        for (int v = 0; v < c; ++v) {
            if (minValueCondenced[v] > maxValueCondenced[v]) {
                NO();
            }
            for (const auto& tv2: condencedGraph[v]) {
                minValueCondenced[tv2.second] = max(minValueCondenced[tv2.second],
                        minValueCondenced[v] + gap(tv2.first));
            }
        }
        cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            cout << minValueCondenced[compId[i]] << "\n";
        }
    }



    return 0;
}
