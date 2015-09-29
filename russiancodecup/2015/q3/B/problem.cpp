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

int f(ll a) {
    int x = int(a % 9);
    if (x == 0)
        x = 9;
    return x;
}

void upd(ll a, ll b, map<int, int>& stat) {
    for (ll x = a; x <= b; ++x) {
        stat[f(x)] += 1;
    }
}

vector<int> stSolve(const map<int, int>& stat) {
    vector<pii> r;
    for (auto kv: stat) {
        r.emplace_back(kv.second, kv.first);
    }
    sort(all(r));
    reverse(all(r));
    vector<int> ans;
    for (size_t i = 0; i < r.size(); ++i) {
        if (r[i].first == r[0].first) {
            ans.push_back(r[i].second);
        }
    }
    sort(all(ans));
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t-->0) {
        ll a,b;
        cin >> a >> b;
        map<int, int> stat;
        if (b - a > 100) {
            ll A = a;
            while(A % 9 != 8) {
                ++A;
            }
            ll B = b;
            while(B % 9 != 0) {
                --B;
            }
            upd(a, A, stat);
            upd(B, b, stat);
        } else {
            upd(a,b, stat);
        }
        auto ans = stSolve(stat);
        cout << ans.size() << " ";
        for (int x: ans) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}
