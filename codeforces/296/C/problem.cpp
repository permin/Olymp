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

void euler(int v, vector<multiset<int>>& al, vi& cycle) {
    stack<int> s;
    s.push(v);
    while (!s.empty()) {
        int v = s.top();
        if (al[v].empty()) {
            s.pop();
            cycle.push_back(v);
        } else {
            auto it = al[v].begin();
            int v2 = *it;
            al[v].erase(it);
            //if (v2 != v) {
            auto it2 = (al[v2].find(v));
            assert(it2 != al[v2].end());
            al[v2].erase(it2);
            s.push(v2);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vi deg(n);
    vector<multiset<int>> al(n);
    for (int i = 0; i < m; ++i) {
        int x,y;
        cin >> x >> y;
        --x;
        --y;
        ++deg[x];
        al[x].insert(y);
        //if (x != y) {
            ++deg[y];
            al[y].insert(x);
        //}
    }
    vi odd;
    for (int i = 0; i < n; ++i)
        if (deg[i] & 1)
            odd.push_back(i);
    debug(odd);
    for (int i = 0; i < odd.size(); ++i) {
        int x = odd[i];
        ++i;
        int y = odd[i];
        al[x].insert(y);
        al[y].insert(x);
    }
    vi cycle;
    euler(0, al, cycle);
    if (cycle.size() & 1)
        cycle.pop_back();
    debug(cycle);
    cout << cycle.size() << "\n";
    vi in(n);
    vi out(n);
    for (int i = 0; i < cycle.size(); ++i) {
        int x = cycle[i];
        int y = cycle[(i + 1) % cycle.size()];
        ++x, ++y;
        if (i & 1) {
            ++out[x - 1];
            ++in[y - 1];
            cout << y << " " << x << "\n";
        } else {
            ++out[y - 1];
            ++in[x - 1];
            cout << x << " " << y << "\n";
        }
    }
    for (int i = 0; i < n; ++i) {
        assert(out[i] % 2 == 0);
        assert(in[i] % 2 == 0);
    }
    return 0;
}
