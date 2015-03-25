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

int main() {
    std::ios_base::sync_with_stdio(false);
    vector<vector<int>> al(10 + 10*10000);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i) {
        for (int d = 1; d * d <= a[i]; ++d) {
            if (a[i] % d)
                continue;
            al[d].push_back(i);
            if (d * d != a[i]) {
                al[a[i]/d].push_back(i);
            }
        }
    }
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        auto e = al[a[i]].end();
        auto it = lower_bound(all(al[a[i]]), i);
        int g = i;
        if (it != e) {
            ++it;
            if (it!=e)
                g = *it;
        }
        int f = i;
        it = lower_bound(all(al[a[i]]), i);
        if (it != al[a[i]].begin()) {
            --it;
            f = *it;
        }
        res += 1LL * a[f] * a[g];
    }
    cout << res << "\n";
    return 0;
}
