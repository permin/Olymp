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

int main() {
    vii sets;
    int n;
    cin >> n;
    int a,b;
    cin >> a >> b;
    vector<int> p(n);
    map<int, int> id;
    set<int> used;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        id[x] = i;
        p[i] = x;
    }
    for (int i = 0; i < n; ++i) {
        int x = p[i];
        if (used.count(x) > 0) {
            continue;
        }
        vi Q;
        int pos = 0;
        Q.push_back(x);
        used.insert(x);
        while (pos < Q.size()) {
            int x = Q[pos++];
            int y = a - x;
            int z = b - x;
            if (id.count(y) && used.count(y) == 0) {
                used.insert(y);
                Q.push_back(y);
            }
            if (id.count(z) && used.count(z) == 0) {
                used.insert(z);
                Q.push_back(z);
            }
        }
        sets.push_back(Q);
    }
    vi ans(n, -1);
    for (int i = 0; i < sets.size(); ++i) {
        set<int> Q(all(sets[i]));
        bool A = true;
        bool B = true;
        for (int x: Q) {
            if (Q.count(a - x) == 0)
                A = 0;
            if (Q.count(b - x) == 0)
                B = 0;
        }
        if (A) {
            for (int x: Q) {
                ans[id.at(x)] = 0;
            }
        } else if (B) {
            for (int x: Q) {
                ans[id.at(x)] = 1;
            }
        } else {
            cout << "NO\n";
            return 0;
        }
    }
    if (count(all(ans), -1)) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
