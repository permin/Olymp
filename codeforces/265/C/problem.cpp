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

const int mod = 1e9 + 7;

int add(int x, int y) {
    int r = x + y;
    if (r >= mod)
        r -= mod;
    return r;
}

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int main() {
    vector<int> mod(10);;
    vector<int> modLen(10);
    for (int i = 0; i < 10; ++i) {
        modLen[i] = 10;
        mod[i] = i;
    }
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> req(n + 1);
    req[0] = "0->" + s;
    for (int i = 0; i < n; ++i) {
        cin >> req[i + 1];
    }
    ++n;
    for (int i = n - 1; i >= 0; --i) {
        vector<int> newMod(mod);
        vector<int> newModLen(modLen);
        int d = req[i][0] - '0';
        newMod[d] = 0;
        newModLen[d] = 1;
        for (int j = req[i].size() - 1; j >= 3; --j) {
            int x = req[i][j] - '0';
            newMod[d] = add(newMod[d], mul(mod[x], newModLen[d]));
            newModLen[d] = mul(newModLen[d], modLen[x]);
        }
        swap(newMod, mod);
        swap(newModLen, modLen);
    }
    cout << mod[0] << "\n";
    return 0;
}
