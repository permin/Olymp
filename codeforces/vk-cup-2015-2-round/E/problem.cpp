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

int add(int x, int y, int mod) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

int mul(int x, int y, int mod) {
    ll res = 1LL * x * y;
    return int(res % mod);
}

int sub(int x, int y, int mod) {
    if (y == 0)
        return x;
    return add(x, mod - y, mod);
}

const int MOD1 = 1e9 + 9;
const int MOD2 = 1e9 + 7;
const int X = 239;

struct Hash {
    Hash(int h1, int h2):
        h1(h1), h2(h2) {}
    Hash():
        h1(0), h2(0) {}

    int h1;
    int h2;
    Hash append(char ch) const {
        int H1 = mul(h1, X, MOD1);
        int H2 = mul(h2, X, MOD2);

        H1 = add(H1, ch, MOD1);
        H2 = add(H2, ch, MOD2);
        return Hash(H1, H2);
    }
};

Hash diff(const Hash& first, const Hash& last) {
    return Hash(sub(last.h1, first.h1, MOD1),
                sub(last.h2, first.h2, MOD2));
}

vector<Hash> f(const string& s) {
    vector<Hash> pref;
    for (size_t i = 0; i < s.size(); ++i) {
        Hash p = i ? pref[i - 1] : Hash();
        pref.push_back(p.append(s[i]));
    }
    for (int i = 0; i <= s.size(); ++i) {
        for (char ch = 'a'; ch <= 'z'; ++ch) {

        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    string s, t;
    cin >> s >> t;


    return 0;
}
