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
template <class T>
ostream& operator << (ostream& o, const multiset<T>& v) {o << "{";O__(o, v);o << "}";return o;}

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::multiset<int> lens;
    std::set<int> positions;
    int n;
    cin >> n;
    positions.insert(-1);
    positions.insert(n);
    lens.insert(n);
    std::vector<pii> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(all(a));
    //reverse(all(a));
    std::vector<pii> ans;
    ans.emplace_back(min_element(all(a))->first, n);
    for (size_t i = 0; i < a.size(); ++i) {
        int pos = a[i].second;
        auto it = positions.insert(pos).first;
        auto nit = std::next(it);
        auto pit = std::prev(it);
        //debug(*nit);
        //debug(*it);
        //debug(*pit);
        //debug(lens);
        //debug(positions);
        lens.erase(lens.find(*nit - *pit - 1));
        lens.insert(*it - *pit - 1);
        lens.insert(*nit - *it - 1);
        if (i + 1 < a.size() && a[i].first != a[i+1].first) {
            ans.emplace_back(a[i+1].first, *lens.rbegin());
        }
    }
    sort(all(ans));
    reverse(all(ans));
    //debug(ans);
    vector<int> res(n, -1);
    int L = 1;
    for (size_t i = 0; i < ans.size(); ++i) {
        while(L <= ans[i].second) {
            //debug(L);
            res[L-1] = ans[i].first;
            ++L;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << res[i] << "  ";
    }
    cout << "\n";


    return 0;
}
