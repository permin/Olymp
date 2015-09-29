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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

template<class T>
bool in(int x, int y, const T& d) {
    return x >= 0 && y >= 0 && x < (int)d.size() && y < (int)d[x].size();
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> plan(n + 2, string(m + 2, '.'));
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        plan[i + 1] = "." + s + ".";
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (plan[i][j] == '.') {
                continue;
            }
            int badDir = 0;
            bool isSelectedDirDad = 0;
            int DX, DY;
            if (plan[i][j] == '<') {
                DX = 0; DY = -1;
            } else if (plan[i][j] == '>') {
                DX = 0; DY = +1;
            } else if (plan[i][j] == '^') {
                DX = -1; DY = 0;
            } else if (plan[i][j] == 'v') {
                DX = +1; DY = 0;
            } else {
                assert(0);
            }
            for (int dx = -1; dx <= +1; ++dx) {
                for (int dy = -1; dy <= +1; ++dy) {
                    if (abs(dx) + abs(dy) != 1) {
                        continue;
                    }
                    int x = i;
                    int y = j;
                    //debug(x);
                    //debug(y);
                    //debug(dx);
                    //debug(dy);
                    do {
                        x += dx;
                        y += dy;
                        if (x == 0 || x == n + 1 || y == 0 || y == m + 1) {
                            ++badDir;
                            if (dx == DX && dy == DY) {
                                isSelectedDirDad = true;
                            }
                            break;
                        }
                    } while(plan[x][y] == '.');
                    //debug(x);
                    //debug(y);
                }
            }
            assert(badDir < 5);
            if (badDir == 4) {
                cout << "IMPOSSIBLE\n";
                return;
            }
            if (isSelectedDirDad) {
                ++res;
            }
        }
    }
    cout << res << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<<t+1<<": ";
        solve();
    }
    return 0;
}
