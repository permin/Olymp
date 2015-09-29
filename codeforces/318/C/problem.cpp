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

void dfs(int v, const vii& al, vi& t, int p = -1) {
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int childs = 0;
    for (int v2: al[v]) {
        if (v2 == p)
            continue;
        ++childs;
        dfs(v2, al, t, v);
        if (t[v2] == 1)
            ++c1;
        if (t[v2] == 2)
            ++c2;
        if (t[v2] == 3)
            ++c3;
    }
    if (c1 + c2 + c3 != childs)
        return;

    if (childs == 0 || (childs == 1 && c1 == 1)) {
        t[v] = 1;
    }
    if (childs == 2 && c1 == 2) {
        t[v] = min(t[v], 2);
    }
    if (c3 <= 1) {
        t[v] = min(t[v], 3);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vii al(n);
    for (int i = 0; i < n - 1; ++i) {
        int a,b;
        cin >> a >> b;
        --a;--b;
        al[a].push_back(b);
        al[b].push_back(a);
    }

    int r = 0;
    for (int i = 1; i < n; ++i) {
        if (al[i].size() > al[r].size()) {
            r = i;
        }
    }
    if (al[r].size() < 3) {
        cout << "Yes\n";
        return 0;
    }
    vi t(n, INF);
    dfs(r, al, t);

    int c3 = 0;
    for (int v: al[r]) {
        if (t[v] == INF) {
            cout << "No\n";
            return 0;
        }
        if (t[v] == 3)
            ++c3;
    }
    if (c3 <= 2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
