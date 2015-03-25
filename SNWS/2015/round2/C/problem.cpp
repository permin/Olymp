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

vii mul(const vii& a, const vii& b) {
    assert(a[0].size() == b.size());
    vii c(a.size(), vi(b[0].size(), 0));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < a[i].size(); ++k) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= 6;
            }
        }
    }
    return c;
}

vii pow(vii A, int n) {
    assert(A.size() == A[0].size());
    vii E(A.size(), vi(A.size()));
    for (int i = 0; i < E.size(); ++i)
        E[i][i] = 1;

    while (n) {
        if (n & 1) {
            --n;
            E = mul(E, A);
        } else {
            A = mul(A, A);
            n /= 2;
        }
    }
    return E;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, k;
    while(cin >> n >> k) {
        if (n == 0)
            break;
        vii A(n, vi(k));
        vii B(k, vi(n));
        for (int i = 0; i < n; ++i)
            for (int j =0; j < k; ++j)
                cin >> A[i][j];
        for (int i = 0; i < k; ++i)
            for (int j =0; j < n; ++j)
                cin >> B[i][j];
        vii AB = mul(B, A);
        assert(AB.size() == k);
        AB = pow(AB, n * n - 1);
        vii res = mul(A, mul(AB, B));
        int sum = 0;
        for (const auto& x: res)
            for (int y: x)
                sum += y;
        cout << sum << "\n";
    }
    return 0;
}
