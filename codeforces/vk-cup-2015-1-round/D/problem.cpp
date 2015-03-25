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

int f(const string& str) {
    int s,h,m;
    //012345678
    //12:13:15
    s = 10 * (str[6] - '0') + str[7] - '0';
    m = 10 * (str[3] - '0') + str[4] - '0';
    h = 10 * (str[0] - '0') + str[1] - '0';
    return h * 60 * 60 + 60 * m + s;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    const int LEN = 86400;
    vii req(LEN);
    int n, m, T;
    cin >> n >> m >> T;
    vi ans(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        req[f(s)].push_back(i);
    }

    deque<pii> pos_color;
    map<int, int> num;
    bool was = false;
    int current = 1;
    for (int t = 0; t < LEN; ++t) {
        while(!pos_color.empty() && pos_color[0].first < t - T + 1) {
            int val = pos_color[0].second;
            num[val] -= 1;
            if (num[val] == 0)
                num.erase(val);
            pos_color.pop_front();
        }

        for (int x = 0; x < req[t].size(); ++x) {
            int ind = req[t][x];
            int color = -1;
            if (num.size() < m) {
                color = current;
                ++current;
            } else {
                assert(!pos_color.empty());
                color = pos_color.back().second;
            }
            pos_color.push_back(pii(t, color));
            num[color] += 1;
            ans[ind] = color;

            assert(num.size() <= m);
            if (num.size() == m)
                was = true;
        }
    }
    if (!was) {
        cout << "No solution\n";
        return 0;
    } else {
        cout << current - 1 << "\n";
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] << "\n";
        }
    }

    return 0;
}
