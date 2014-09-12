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

class PotentialArithmeticSequence{
public:
    bool test(vi x) {
        if (x.size() == 1)
            return 1;
        vi y;
        for (int i = 0; i < x.size(); ++i) {
            if (x[i])
                y.push_back(x[i] - 1);
            if (i && ((x[i] == 0) == (x[i-1]==0)))
                return 0;
        }
        return test(y);
    }
    int numberOfSubsequences(vector <int> d) {
        int res = 0;
        for (int i = 0; i < d.size(); ++i) {
            for (int j = i + 1; j <= d.size(); ++j) {
                vi x(d.begin() + i, d.begin() + j);
                res += test(x);
            }
        }
        return res;
    }
};

int main() {
    PotentialArithmeticSequence A;
    debug(A.numberOfSubsequences({0,0,0,0,1,1,1}));
    debug(A.numberOfSubsequences({0,1,0,2,0,1,0}));
    debug(A.numberOfSubsequences({0,100,0,2,0}));
    debug(A.numberOfSubsequences({1,11,3,0,1,0,1,0,1,0,1,0,3,0,2,0,0,0,0,1,2,3,20}));
    return 0;
}
