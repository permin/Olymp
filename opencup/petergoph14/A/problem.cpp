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
const int INF = std::numeric_limits<int>::max() / 3;
const long long LLINF = std::numeric_limits<ll>::max();

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

int solve(int t, int mask, vii& dp, vii& to, const vi& w, const vi& c) {
    if (t == c.size())
        return solve(0, mask, dp, to, w, c);

    if (mask == 0)
        return 0;
    int &res = dp[t][mask];
    if (res >= 0)
        return res;
    res = 0;
    if (t == 0)
        ++res;
    int cur = INF;
    if (t) {
        to[t][mask] = 0;
        cur = solve(t + 1, mask, dp, to, w, c);
    }
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        if (c[t] >= w[sub]) {
            int a = solve(t + 1, mask ^ sub, dp, to, w, c);
            if (cur > a) {
                to[t][mask] = sub;
                cur = a;
            }
        }
    }
    res += cur;
    res = min(res, INF);
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("dhl.in", "r", stdin);
    freopen("dhl.out", "w", stdout);
    int t, items;
    while(cin >> t >> items) {
        vi c(t);
        vector<pii> sortedC;
        for (int i = 0; i < t; ++i) {
            cin >> c[i];
            sortedC.push_back(pii(c[i], i));
        }
        sort(all(sortedC));
        reverse(all(sortedC));
        for (int i = 0; i < c.size(); ++i){
            c[i] = sortedC[i].first;
        }

        //debug(c);

        vi w(items);
        for (int i = 0; i < items; ++i)
            cin >> w[i];
        vi w2(1 << items);
        for (int i = 0; i < (1 << items); ++i) {
            for (int j = 0; j < items; ++j) {
                if (i & (1 << j))
                    w2[i] += w[j];
            }
        }
        vii dp(t, vi(1 << items, -1));
        vii to = dp;
        int a = solve(0, (1 << items) - 1, dp, to, w2, c);
        if (a >= INF){
            cout << "-1\n";
            continue;
        }
        {
            cout << a << "\n";
            int mask = (1 << items) - 1;
            int tr = 0;
            vector<pii> step;
            while (mask) {
                int sub = to[tr][mask];
                for (int i = 0; i < w.size(); ++i) {
                    if (sub & (1 << i))
                        step.push_back(pii(i, sortedC[tr].second));
                }
                mask ^= sub;
                tr += 1;
                if (tr == t) {
                    cout << step.size() << " ";
                    for (int i = 0; i < step.size(); ++i) {
                        cout << step[i].first + 1 << " " << step[i].second + 1 << " ";
                    }
                    cout << "\n";
                    step.clear();
                    tr = 0;
                }
            }
            if (!step.empty()) {
                cout << step.size() << " ";
                for (int i = 0; i < step.size(); ++i) {
                    cout << step[i].first + 1 << " " << step[i].second + 1 << " ";
                }
                cout << "\n";
            }

        }

    }
    return 0;
}
