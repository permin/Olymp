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

vector<int> numbers;
string a[] = {"123", "456", "789", "*0*"};
string cur;

void gen(int i, int j) {
    if (!cur.empty()) {
        stringstream o;
        o << cur;
        int x;
        o >> x;
        numbers.push_back(x);
    }
    if (cur.size() >= 3) {
        return;
    }
    if (i > 3 || j > 2)
        return;
    if (a[i][j] == '*')
        return;
    cur += a[i][j];
    gen(i + 1, j);
    gen(i, j);
    gen(i, j+1);
    cur.pop_back();

    gen(i + 1, j);
    gen(i, j+1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            gen(i,j);

    sort(all(numbers));
    numbers.erase(unique(all(numbers)), numbers.end());
    //debug(numbers);
    while(t-->0) {
        int k;
        cin >> k;
        int res = INF;
        int c = -1;
        auto it = lower_bound(all(numbers), k);
        res = abs(*it - k);
        c = *it;
        if (it != numbers.begin()) {
            --it;
            if (res > abs(*it - k))
                c = *it;
        }
        cout << c << "\n";
    }
    return 0;
}
