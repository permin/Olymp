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
const int INF = std::numeric_limits<int>::max() / 3;
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

struct First {
    bool operator()(const pii& a, const pii& b) const {
        if (a.first != b.first)
            return a.first < b.first;
        return a.second < b.second;
    }
};

struct Second {
    bool operator()(const pii& a, const pii& b) const {
        if (a.first != b.first)
            return a.first < b.first;
        return a.second < b.second;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    set<int, std::less<int>> Less;
    set<int, std::greater<int>> Greater;

    int n;
    cin >> n;

    vi indeg(n, 0);
    vi outdeg(n, 0);
    vi minPredDeg(n, INF);

    vii al(n);
    vii tal(n);

    map<pii, int> cubes;

    vector<bool> onAFloor(n);

    vector<pii> data;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        cubes[pii(x,y)] = i;
        data.push_back(pii(x,y));
    }

    for (int i = 0; i < n; ++i) {
        int x = data[i].first;
        int y = data[i].second;

        if (y == 0)
            onAFloor[i] = 1;

        for (int dx = -1; dx <= +1; ++dx) {
            int nx = x + dx;
            int ny = y - 1;

            if (cubes.count(pii(nx, ny))) {
                al[i].push_back(cubes[pii(nx, ny)]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int x: al[i]) {
            tal[x].push_back(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        outdeg[i] = (int)al[i].size();
        indeg[i] = (int)tal[i].size();
    }
    for (int i = 0; i < n; ++i) {
        for (int p: tal[i]) {
            minPredDeg[i] = min(minPredDeg[i], outdeg[p]);
        }
    }

    vector<bool> alive(n, 1);

    auto check = [&](int x) {
        return alive[x] && (indeg[x] == 0 || minPredDeg[x] > 1);
    };

    auto doit = [&](int x) {
        if (check(x)) { Less.insert(x); Greater.insert(x);} else {Less.erase(x); Greater.erase(x);};
    };



    debug(minPredDeg);
    for (int i =0 ; i < n; ++i) {
        doit(i);
    }

    int rem = n;
    bool mi = false;
    vi res;

    debug(al);
    debug(tal);




    while(rem > 0) {
        debug(Less);
        int v = mi ? *Less.begin() : *Greater.begin();
        mi = !mi;

        res.push_back(v);

        alive[v] = false;
        doit(v);

        vi consider;

        for (int p: tal[v]) {
            if (alive[p]) {
                outdeg[p] -= 1;
                for (int s: al[p]) {
                    if (!alive[s])
                        continue;

                    minPredDeg[s] = INF;
                    for (int p2: tal[s]) {
                        if (alive[p2]) {
                            minPredDeg[s] = min(minPredDeg[s], outdeg[p2]);
                        }
                    }

                    doit(s);
                }
                doit(p);
            }
        }


        for (int s: al[v]) {
            if (alive[s]) {
                indeg[s] -= 1;

                minPredDeg[s] = INF;

                for (int p: tal[s]) {
                    if (alive[p]) {
                        minPredDeg[s] = min(minPredDeg[s], outdeg[p]);
                    }
                }

                doit(s);
            }
        }

        --rem;
    }

    debug(res);

    ll ans = 0;
    const ll MOD = ll(1e9 + 9.5);
    for (int x: res) {
        ans *= n;
        ans += x;
        ans %= MOD;
    }

    cout << ans << "\n";


    return 0;
}
