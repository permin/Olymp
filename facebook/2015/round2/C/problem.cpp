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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

struct Node {
    Node():
        to(26, -1),
        num(0),
        terminal(false),
        depth(0){}
    vi to;
    size_t num;
    bool terminal;
    int depth;
};

ostream& operator << (ostream& o, const Node& v) {
    return o << v.to << " " << v.num << " " << v.terminal << " " << v.depth << "\n";
}
int real(vector<Node>& trie) {
    trie.push_back(Node());
    return int(trie.size()) - 1;
}

void add(vector<Node>& trie, const std::string& s) {
    int cur = 0;
    trie[cur].num += 1;

    for (int i = 0; i < s.size(); ++i) {
        int ind = s[i] - 'a';
        if (trie[cur].to[ind] == -1)
            trie[cur].to[ind] = real(trie);
        cur = trie[cur].to[ind];
        trie[cur].depth = i + 1;
        trie[cur].num += 1;
    }
    assert(trie[cur].terminal == false);
    trie[cur].terminal = true;
}

int solve(int state, int minChar, int k, viii& dp, const vector<Node>& trie) {
    assert(state < trie.size());
    assert(k >= 0);
    int &res = dp[state][minChar][k];
    if (k == 0)
        return res = 0;
    // k > 0
    if (res >= 0)
        return res;
    res = INF;
    if (minChar == 26) {
        return res;
    }
    if (k == 1 && trie[state].to[minChar] != -1) {
        return res = min(res, trie[state].depth + 1);
    }
    for (int x = 0; x <= k; ++x) {
        if (x == 0) {
            res = min(res, solve(state, minChar + 1, k, dp, trie));
        } else {
            int newState = trie[state].to[minChar];
            if (newState == -1)
                break;
            if (trie[newState].num < x)
                break;
            res = min(res,
                    solve(newState, 0, x, dp, trie) +
                    solve(state, minChar + 1, k - x, dp, trie) );
            if (trie[newState].num > 0 && x == 1) {
                res = min(res,
                        solve(state, minChar + 1, k - x, dp, trie) +
                        solve(newState, 0, x - 1, dp, trie) +
                        trie[newState].depth);
            }
            if (trie[newState].terminal) {
                res = min(res,
                        solve(state, minChar + 1, k - x, dp, trie) +
                        solve(newState, 0, x - 1, dp, trie) +
                        trie[newState].depth);
            }
        }
    }
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<Node> trie(1);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add(trie, s);
    }
    //debug(trie);
    //debug(trie.size());
    viii dp(trie.size(), vii(27, vi(k + 1, -1)));
    cout << solve(0, 0, k, dp, trie) << "\n";
    //debug(dp[0][0][k]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<<t+1<<": ";
        solve();
    }
    return 0;
}
