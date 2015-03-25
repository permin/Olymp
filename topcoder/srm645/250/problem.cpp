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

class JanuszTheBusinessman {
public:
    /*void dfs(int v, const vii& al, vector<bool>& used) {
        if (used[v])
            return;
        used[v] = 1;
        for (int v2: al[v])
            dfs(v2, al, used);
    }
    bool inter(int a, int b, int x, int y) {
        for (int i = a; i<= b; ++i)
            if (x <=i && i <= y)
                return 1;
        return 0;
    }
    int makeGuestsReturn(vector <int> arrivals, vector <int> departures){
        int n = int(arrivals.size());
        vii al(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (inter(arrivals[i], departures[i], arrivals[j], departures[j])) {
                    al[i].push_back(j);
                    al[j].push_back(i);
                }
            }
        }
        vector<bool> used(n, 0);
        int c = 0;
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                ++c;
                dfs(i, al, used);
            }
        }
        return c;
    }*/

    bool betw(int i, const pii& a) {
        return a.first <= i && i <= a.second;
    }
    bool inter(const pii& a, const pii& b) {
        return betw(a.first, b) || betw(a.second, b) || betw(b.first, a) || betw(b.second, a);
    }
    int solve(const vector<pii>& a, int p, vector<int>& dp) {
        if (p == a.size())
            return 0;
        int& res = dp[p];
        if (res >= 0)
            return res;
        res = INF / 2;
        for (int i = p; i < a.size(); ++i) {
            bool ok = 1;
            for (int j = p; j <= i; ++j) {
                if (!inter(a[i], a[j]))
                    ok = 0;
            }
            if (!ok)
                continue;
            int x = i;
            while(x < a.size() && inter(a[x], a[i])) {
                res = min(res, 1 + solve(a, x + 1, dp));
                ++x;
            }
        }
        return res;
    }
    int makeGuestsReturn(vector <int> arrivals, vector <int> departures){
        int n = int(arrivals.size());
        vector<pii> a;
        for (int i =0 ;i < n; ++i)
            a.push_back(pii(arrivals[i], departures[i]));
        sort(all(a));
        vector<int> dp(n + 1, -1);
        return solve(a, 0, dp);
    }

};

int main() {
    return 0;
}
