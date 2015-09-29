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

class RandomPancakeStack
{
public:
	double expectedDeliciousness(vector <int> d)
	{
        int n = (int)d.size();
        vector<vector<double>> dp(n+1,vector<double>(n+1, 0.0));
        for (int bound = 1; bound <= n; ++bound) {
            for (int size = bound; size <= n; ++size) {
                for (int i = 0; i < bound; ++i) {
                    dp[bound][size] += 1.0 / size * (d[i] + dp[i][size - 1]);
                }
            }
        }
        return dp[n][n];
	}
	double expectedDeliciousnessWrong(vector <int> d) {
        int n = (int)d.size();
        vector<vector<double>> dp(n+1,vector<double>(n+1, 0.0));
        for (int bound = 1; bound <= n; ++bound) {
            for (int size = bound; size <= n; ++size) {
                for (int i = 0; i < bound; ++i) {
                    dp[bound][size] += 1.0000 / (size) * (d[i] + dp[i][size - 1]);
                }
            }
        }
        return dp[n][n];
    }
};

int main() {
    //std::ios_base::sync_with_stdio(false);
    {
        int n = 1000*1000;
        int m = 2450;
        int d = n / m;
        vi a;
        for (int i = 2; i + 6 < n && a.size() < m; i += d) {
            a.push_back(i);
            a.push_back(i+1);
            a.push_back(i+2);
        }
        std::random_shuffle(all(a));
        for (size_t i = 0; i < a.size(); ++i) {
            if (i)
                cout << ",";
            cout << a[i];
        }
        return 0;
    }
    int it = 0;
    while(true) {
        ++it;
        debug(it);
        int n = 250;
        vi d;
        for (int i = 0; i < n; ++i) {
            d.push_back(1 + (rand() % 1000));
        }
        double myAns = RandomPancakeStack().expectedDeliciousness(d);
        double newAns = RandomPancakeStack().expectedDeliciousnessWrong(d);
        if (fabs(myAns - newAns) > 1e-6) {
            printf("my: %0.18f new: %0.18f\n", myAns, newAns);
            for (int i = 0; i < n; ++i) {
                cerr << d[i] << ",";
            }
            cerr << "\n";
            break;
        }

    }
    return 0;
}
