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

string cur;
string path;
string ans;
bool br;
string a[4];
bool am[4][4];

int dx[] = {-1,+1,0,0};
int dy[] = {0,0,-1,+1,0,0};
string sym = "UDLR";

void solve(int x, int y) {
    if (br)
        return;
    if (x == y && x == 3) {
        if (path.empty()) {
            path = cur;
            return;
        }
        if (path.size() > cur.size()) {
            swap(path, cur);
        }
        if (path.size() < cur.size()) {
            ans = cur;
            br = 1;
        }
        return;
    }
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4 || am[nx][ny] == 1) {
            continue;
        }
        am[nx][ny] = 1;
        cur.push_back(sym[d]);
        solve(nx, ny);
        cur.pop_back();
        am[nx][ny] = 0;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("nsp.in", "r", stdin);
    freopen("nsp.out", "w", stdout);
    string s;
    while (true) {
        cin >> a[0] >> a[1] >> a[2] >> a[3];
        /*debug(a[0]);
        debug(a[1]);
        debug(a[2]);
        debug(a[3]);*/
        cur = path = ans = "";
        br = 0;
        for (int i= 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                am[i][j] = (a[i][j] == '#');
        am[0][0] = 1;
        solve(0,0);
        //debug(path);
        if (ans.empty()) {
            cout << "-1\n";
        } else {
            cout << ans << "\n";
        }
        s = "";
        cin >> s;
        if (s != "----")
            break;
    }
    return 0;
}
