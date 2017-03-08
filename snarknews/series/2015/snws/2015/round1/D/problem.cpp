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

double A(const vector<double>& a) {
    return std::accumulate(all(a),0.0) / double(a.size());
}

double doit(int n) {
    vector<bool> used(n, 0);
    int k = n;
    int it = 0;
    while(k > 0) {
        ++it;
        int i = rand() % n;
        if (used[i])
            continue;
        used[i] = true;
        --k;
    }
    return 1.0 * it;
}

double solve(int n) {
    //double av = -1.0;
    vector<double> a;
    for(int it = 0; it < 1e6; ++it)
        a.push_back(doit(n));
    /*while(fabs(av - A(a)) < 0.001) {
        debug(av);
        av = A(a);
        a.push_back(doit(n));
    }*/
    //debug(a)
    return A(a);
}

double f(int k, vector<double>& dp) {
    int n = int(dp.size()) - 1;
    if (k == 0)
        return 0.0;
    dp[k] = (1 + 1.0 * k / n * f(k - 1, dp)) * (1.0 * n / k);
    return dp[k];
}

int main() {

    //for (int n = 2; n <= 100; ++n) {
        int n;
        cin >> n;
        vector<double> dp(n + 1, -1.0);
        printf("%0.18lf\n", f(n, dp));
        //cout << n << " " << solve(n) << " " << f(n, dp) << "\n";
    //}

    return 0;
}
