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

int main() {
    int n, p;
    cin >> n >> p;
    string s;
    cin >> s;
    if (p == 1 || (p == 2 && s[0] == 'b') ) {
        cout << "NO\n";
        return 0;
    }
    if (p == 2) {
        if (n == 1) {
            cout << "b";
        } else {
            cout << "ba";
        }
        return 0;
    }
    char z = 'a' + p - 1;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == z)
            continue;
        s[i] += 1;
        if ((i && s[i - 1] == s[i]) || (i - 2 >= 0 && s[i - 2] == s[i])) {
            if (s[i] == z)
                continue;
            s[i] += 1;
        }
        if ((i && s[i - 1] == s[i]) || (i - 2 >= 0 && s[i - 2] == s[i])) {
            if (s[i] == z)
                continue;
            s[i] += 1;
        }
        for (int j = i + 1; j < s.size(); ++j) {
            bool ok = 0;
            for (int ch = 'a'; ch <= z;++ch) {
                s[j] = ch;
                if (j - 1 >= 0 && s[j] == s[j - 1])
                    continue;
                if (j - 2 >= 0 && s[j] == s[j - 2])
                    continue;
                ok = 1;
                break;
            }
            if (!ok)
                continue;
        }
        cout << s << "\n";
        return 0;
    }
    cout << "NO\n";
    return 0;
}
