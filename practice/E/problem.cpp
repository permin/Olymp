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

class Dsu {
    public:
        Dsu(int x) {
            for (int i = 0; i < x; ++i)
                par.push_back(i);
        }
        int getPar(int x) {
            return x == par[x] ? x : par[x] = getPar(par[x]);
        }
        bool merge(int x, int y) {
            x = getPar(x);
            y = getPar(y);
            par[x] = y;
            return x != y;
        }
        vi par;
};

int main() {
    char a = 'a';
    char b = 'b';
    char c = 'c';
    char d = 'd';
    char e = 'e';
    char f = 'f';
    char g = 'g';
    char h = 'h';
    char i = 'i';
    char j = 'j';

    map<char, pii> first;
    map<char, pii> second;
    first[a] = pii(1,0);
    first[b] = first[a];
    first[c] = first[d] = pii(0,2);
    first[e] = pii(0,5);
    first[f] = pii(3, 5);
    first[g] = pii(4, 5);
    first[h] = pii(3,4);
    first[i] = pii(2,3);
    first[j] = pii(1,2);

    second[a] = pii(0, 5);
    second[b] = pii(0, 2);
    second[c] = pii(0,1);
    second[d] = pii(1,2);
    second[e] = second[f] = pii(2,3);
    second[g] = second[h] = pii(3, 4);
    second[i] = pii(2, 4);
    second[j] = pii(4, 5);

    debug(first.size());
    debug(second.size());


    for (int mask = 0; mask < (1 << first.size()); ++mask) {
        if (__builtin_popcount(mask) == 5) {
            Dsu d1(6);
            Dsu d2(6);
            bool ok = true;
            for (int i = 0; i < first.size(); ++i) {
                if (mask & (1 << i)) {
                    char ch = 'a' + i;
                    ok = ok && d1.merge(first[ch].first, first[ch].second);
                    ok = ok && d2.merge(second[ch].first, second[ch].second);
                }
            }
            if (ok) {
                for (int i = 0; i < first.size(); ++i) {
                    if (mask & (1 << i)) {
                        char ch = 'a' + i;
                        cerr << ch << " ";
                    }
                }
                cerr << "\n";
            }
        }
    }

    return 0;
}
