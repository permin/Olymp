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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
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
const long long LLINF = std::numeric_limits<ll>::max() / 2;

// supports find_by_order(int) and order_of_key(Key)
const int SUM = 41 * 11;
const int NUM = 11;

vector<vector<double>> max_sum(SUM, vector<double>(NUM, -1.0));
vector<vector<double>> min_sum(SUM, vector<double>(NUM, 1e10));
vector<vector<bool>> calc(SUM, vector<bool>(NUM, false));

double f(int s) {
    s += 60;
    if (85 <= s)
        return 4.0;
    if (80 <= s)
        return 3.5;
    if (75 <= s)
        return 3.0;
    if (70 <= s)
        return 2.5;
    return 2.0;
}

void g(int sum, int num) {
    if (calc[sum][num]) {
        return;
    }

    if (num == 0) {
        if (sum == 0) {
            max_sum[sum][num] = min_sum[sum][num] = 0.0;
        } else {
            max_sum[sum][num] = -INF;
            min_sum[sum][num] = +INF;
        }
        calc[sum][num] = 1;
        return;
    }

    for (int i = 0; i <= 40; ++i) {
        if (i <= sum) {
            g(sum - i, num - 1);
            max_sum[sum][num] = max(max_sum[sum][num],
                    f(i) + max_sum[sum - i][num - 1]);
            min_sum[sum][num] = min(min_sum[sum][num],
                    f(i) + min_sum[sum - i][num - 1]);
        }
    }

    calc[sum][num] = 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while(t-->0){
        int s, n;
        cin >> s >> n;
        s = (s - 60) * n;
        g(s, n);
        printf("%0.18lf %0.18lf\n", min_sum[s][n] / n, max_sum[s][n]/n);
    }

    return 0;
}
