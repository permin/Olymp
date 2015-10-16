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


const int mod  = 1000*1000*1000 + 7;
int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

bool g(int mask, int pos) {
    return mask & (1 << pos);
}

struct T {};

struct E: public T {
    explicit E(size_t l, size_t e, char o):
        left(l),right(r), op(o){}
    size_t left, right;
    char op;
};

struct V: public T {
    explicit V(char ch): ch(ch){}
    char ch;
};

std::vector<T*> expt;

int varMask[256];

template<class It>
size_t go(It begin, It end) {
    if (begin + 1 == end) {
        size_t id = expt.size();
        expt.push_back(new V(*begin));
        return id;
    }
    It mid = begin;
    int bal = 0;
    do {
        if (*mid == '(')
            ++bal;
        if (*mid == ')')
            --bal;
        ++mid;
    } while(bal > 0);
    size_t l = go(begin + 1, mid);
    size_t r = go(mid + 1, end);
    char c = *mid;
    size_t id = expt.size();
    expt.push_back(new E(l, r, c));
    return id;
}

int solve(int v, int truth, vii& dp) {
    int & res = dp[v];
    if (res >= 0)
        return res;
    res = 0;
    if (V* var = dynamic_cast<V*>(expt[v])) {
        if (var->
    } else {
        E* e = dynamic_cast<E*>(
    }
}

int main() {

    {
        for (char ch: "abcdABCD") {
            int mask = 0;
        }
    }

    std::ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    go(s);
    int n;
    cin >> n;
    map<int, bool> data;
    for (int i = 0; i < n; ++i) {
        int a,b,c,d,e;
        cin >> a >> b >> c >> d >> e;
        data[a * 8 + b * 4 + c * 2 + d] = e;
    }
    int res =0 ;

    vii dp(expt.size(), vi((1 << 16), -10));

    for (int mask = 0; mask < (1<<16); ++i) {
        bool ok = 1;
        for (int i = 0; i < (1<<4); ++i) {
            if (data.count(i) && data[i] != g(mask, i))
                ok = 0;
        }
        if (ok) {
            res = add(res, solve(0, mask, dp));
        }
    }
    cout << res << "\n";

    return 0;
}
