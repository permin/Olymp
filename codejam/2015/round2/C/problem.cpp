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

typedef std::set<string> Set;
typedef std::map<string, int> Map;

int res = INF;
int cur = 0;

void rec(int pos, const std::vector<vector<string>>& sentences,
        Map& eng, Map& fra) {
    if (pos == (int) sentences.size()) {
        res = min(res, cur);
        return;
    }
    {
        for (const auto& x: sentences[pos]) {
            if (eng[x] == 0 && fra[x] > 0) {
                ++cur;
            }
            eng[x] += 1;
        }
        rec(pos + 1, sentences, eng, fra);
        for (const auto& x: sentences[pos]) {
            if (eng[x] == 1 && fra[x] > 0) {
                --cur;
            }
            eng[x] -= 1;
        }
    }
    {
        for (const auto& x: sentences[pos]) {
            if (fra[x] == 0 && eng[x] > 0) {
                ++cur;
            }
            fra[x] += 1;
        }
        rec(pos + 1, sentences, eng, fra);
        for (const auto& x: sentences[pos]) {
            if (fra[x] == 1 && eng[x] > 0) {
                --cur;
            }
            fra[x] -= 1;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    std::vector<vector<string>> sentences(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, s);
        stringstream o(s);
        string x;
        while(o >> x) {
            sentences[i].push_back(x);
        }
    }

    Map fra, eng;
    res = INF;
    cur = 0;
    for (const auto& x:sentences[0]) {
        eng[x] += 1;
    }
    for (const auto& x:sentences[1]) {
        if (eng[x] > 0 && fra[x] == 0) {
            ++cur;
        }
        fra[x] += 1;
    }
    rec(2, sentences, eng, fra);

    cout << res << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    debug(tests);
    for (int t = 0; t < tests; ++t) {
        debug(t);
        cout << "Case #"<<t+1<<": ";
        solve();
    }
    return 0;
}
