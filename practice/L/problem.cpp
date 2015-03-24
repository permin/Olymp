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
#include <atomic>
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

vi a;
vi o;
vi l;

class CountryGroupHard
{
public:

    int solve(int pos, const vi& a, vi& dp) {
        int &res = dp[pos];
        if (res >=0 )
            return res;
        res = 0;
        for (int i = 1; i + pos - 1 < a.size(); ++i) {
            bool ok = 1;
            for (int j = 0; j < i; ++j) {
                int p = pos + j;
                if (p >= (int)a.size()) {
                    ok = 0;
                    break;
                }
                if (a[p] != 0 && a[p] != i) {
                    ok = 0;
                    break;
                }
            }
            if (ok)
                res += solve(pos + i, a, dp);
        }
        return res;
    }

	int solve(vector <int> a)
	{
        int n = (int) a.size();
        vi dp(n + 1, -1);
        dp.back() = 1;
        return solve(0, a, dp);
	}
};

void doit(int pos, int prod, int sum) {
    if (sum < 0)
        return;
    if (pos == o.size())
        return;
    if (prod == 1 && !a.empty()) {
        std::cerr << "Win!!!\n";
        debug(a);
        exit(0);
    }
    doit(pos + 1, prod, sum);
    a.push_back(o[pos]);
    doit(pos, prod * o[pos], sum - l[pos] - (a.empty()? 0:1));
    a.pop_back();
}

vi gen(int n, int m) {
    vi res;
    for (int i = 0; i < n; ++i) {
        res.push_back(rand() % m);
    }
    return res;
}

int main() {
    map<int, int> len;
    {
        int it = 100*10000;
        CountryGroupHard solver;
        while(it-->0){
            vi a = gen(1 + rand() % 21, 1 + (rand() % 5));
            int x = solver.solve(a);
            if (x & 1) {
                if (x == 1)
                    continue;
                if (len.count(x) == 0)
                    len[x] = INF;
                len[x] = min(len[x], int(a.size()));
            }
        }
    }
    debug(len);
    for (auto kv: len) {
        int ll, oo;
        ll = kv.second;
        oo = kv.first;
        l.push_back(ll);
        o.push_back(oo);
    }
    doit(0, 1, 100);
    return 0;
}
