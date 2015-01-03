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

class GCDLCM{
public:
    vector<pii> factor(int n) {
        vector<pii> r;
        for (int i = 2; i * i <= n; ++i) {
           int c = 0;
           while(n % i == 0) {
               n /= i;
               ++c;
           }
           if (c)
               r.push_back(pii(i, c));
        }
        if (n > 1)
            r.push_back(pii(n, 1));
        return r;
    }
    void dfs(int v, const vii& al, vi& co, vi& o, int c) {
        if (co[v] != -1)
            return;
        co[v] = c;
        for (int v2: al[v]) {
            dfs(v2, al, co, o, c);
        }
        o.push_back(v);
    }
    vi condence(const vii& al) {
        vi order;
        vi used(al.size(), -1);
        for (int i = 0; i < al.size(); ++i) {
            dfs(i, al, used, order, 1);
        }
        reverse(all(order));
        vi _;
        vi co(al.size(), -1);
        int c = 0;
        vii tal(al.size());
        for (int i = 0; i < al.size(); ++i) {
            for (int v2 : al[i]) {
                tal[v2].push_back(i);
            }
        }
        for (int i = 0; i < order.size(); ++i) {
            if (co[order[i]] == -1)
                dfs(order[i], tal, co, _, c++);
        }
        return co;
    }
    void add(bool xx, int x, bool yy, int y, vii& al) {
        //const int CC = 3;
        int b = al.size() / 2;
        /*std::cerr << "(" << (xx?"":"!") << char('a' + (x/CC)) << (x%CC) << "," <<
            (yy?"":"!") << char('a' + (y/CC)) << (y % CC)
            << ") \n";*/
        al[(!xx) * b + x].push_back(yy * b + y);
        al[(!yy) * b + y].push_back(xx * b + x);
    }
    std::string possible(int n, std::string type, vi A, vi B, vi C) {
        /*for (int i = 0; i < C.size(); ++i) {
            int x = 1;
            while (C[i] / x % 2 == 0)
                x *= 2;
            C[i] = x;
        }*/

        map<int, int> pow;
        for (int c: C) {
            for (pii np: factor(c)) {
                pow[np.first] = max(pow[np.first], np.second);
            }
        }
        for (pii np: pow) {
            //debug(np);
            vi p(C.size());
            for (int i = 0; i < C.size(); ++i) {
                int c = C[i];
                while(c % np.first == 0) {
                    ++p[i];
                    c /= np.first;
                }
            }
            int mp = np.second + 2;
            vii al(n * mp * 2);
            int bound = n * mp;
            // i * mp + j
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j + 1 < mp; ++j) {
                    add(true, i * mp + j, false, i * mp + j + 1, al);
                }
                add(true, i * mp, true, i * mp, al);
                add(false, i * mp + mp - 1, false, i * mp + mp - 1, al);
            }
            for (int i = 0; i < A.size(); ++i) {
                int x = A[i];
                int y = B[i];
                if (type[i] == 'G') {
                    // x >= p[i]
                    add(true, x * mp + p[i], true, x * mp + p[i], al);
                    // y >= p[i]
                    add(true, y * mp + p[i], true, y * mp + p[i], al);
                    // x < p[i] + 1 || y < p[i] + 1
                    add(false, x * mp + p[i] + 1, false, y * mp + p[i] + 1, al);
                } else {
                    // x < p[i] + 1
                    add(false, x * mp + p[i] + 1, false, x * mp + p[i] + 1, al);
                    // y < p[i] + 1
                    add(false, y * mp + p[i] + 1, false, y * mp + p[i] + 1, al);
                    // x >= p[i] || y >= p[i]
                    add(true, x * mp + p[i], true, y * mp + p[i], al);
                }
            }
            for (int i = 0; i < al.size(); ++i) {
                sort(all(al[i]));
                al[i].erase(unique(all(al[i])), al[i].end());
            }
            //debug(al);
            vi cond = condence(al);
            //debug(cond);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < mp; ++j) {
                    if (cond[i * mp + j] == cond[bound + i * mp + j])
                        return "Solution does not exist";
                }
        }
        return "Solution exists";
    }
};

int main() {
    GCDLCM A;
    assert(A.possible(
                3, "GL", {0, 0}, {1, 2}, {3, 1000}) == 	"Solution does not exist"	);
    assert(A.possible(
                5, "GLGLGLGLGL", {0, 0, 1, 1, 2, 2, 3, 3, 4, 4}, {1, 1, 2, 2, 3, 3, 4, 4, 0, 0}, {6, 12, 6, 12, 6, 12, 6, 12, 6, 12}	) == "Solution does not exist");
    assert(A.possible(
            183, "GLGGLG", {54, 138, 172, 57, 33, 174}, {35, 85, 21, 117, 61, 149}, {10, 9763606, 1, 1, 25547744, 1}	) == "Solution exists");
    assert(A.possible(
            4, "GLGLGLGL", {0, 0, 1, 1, 2, 2, 3, 3}, {1, 1, 2, 2, 3, 3, 0, 0}, {6, 12, 6, 12, 6, 12, 6, 12}
                ) == "Solution exists");
    assert(A.possible(
                146, "LLLLLLLLLGGGGLLGGLLLGGGGGGGGGGLLLLGLLLGLGLGGLGGGGGLGGGLGGGLLGGGGLGGGLGLLLG", {139, 63, 14, 40, 85, 121, 36, 98, 42, 73, 122, 125, 39, 58, 28, 26, 70, 27, 104, 86, 17, 72, 61, 85, 121, 107, 0, 85, 128, 21, 128, 52, 3, 0, 4, 7, 90, 4, 113, 16, 119, 80, 109, 128, 9, 104, 127, 129, 10, 90, 131, 33, 112, 109, 11, 29, 58, 36, 47, 11, 133, 54, 24, 77, 59, 19, 42, 56, 136, 113, 143, 99, 121, 70}, {68, 50, 140, 9, 14, 11, 24, 31, 59, 139, 69, 43, 95, 69, 74, 124, 2, 103, 123, 29, 78, 124, 39, 41, 7, 21, 2, 45, 47, 12, 86, 14, 40, 81, 97, 92, 11, 85, 10, 77, 102, 33, 78, 13, 98, 129, 95, 99, 41, 8, 12, 112, 85, 96, 38, 112, 69, 52, 85, 142, 14, 88, 31, 55, 122, 103, 43, 12, 106, 17, 73, 107, 34, 5}, {14639476, 147695434, 50877740, 519808124, 154501020, 763435, 11457726, 12571806, 69760196, 2, 3, 2, 1, 12291321, 417489234, 1, 2, 1, 131876360, 6724521, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1902, 390540, 302479804, 2193642, 4, 95473836, 74048930, 52301052, 1, 7022024, 1, 60593754, 1, 2, 279603012, 2, 1, 2, 1, 1, 544156106, 1, 3, 262052409, 48339510, 3, 1, 138, 600888861, 499005, 1, 2, 1, 1, 105740844, 3, 1, 2, 265569466, 1, 54386892, 2308320, 4775541, 1}) == "Solution does not exist");
    assert(A.possible(
                5, "GLGLGLGLGL", {0, 0, 1, 1, 2, 2, 3, 3, 4, 4}, {1, 1, 2, 2, 3, 3, 4, 4, 0, 0}, {1, 2, 1, 2, 1, 2, 1, 2, 1, 2}
                ) == 	"Solution does not exist"	);
    assert(A.possible(
                5, "GLGLGLGLGL", {0, 0, 1, 1, 2, 2, 3, 3, 4, 4}, {1, 1, 2, 2, 3, 3, 4, 4, 0, 0}, {2, 4, 2, 4, 2, 4, 2, 4, 2, 4}
                ) == 	"Solution does not exist"	);
    assert(A.possible(
                5, "GLGLGLGLGL", {0, 0, 1, 1, 2, 2, 3, 3, 4, 4}, {1, 1, 2, 2, 3, 3, 4, 4, 0, 0}, {6, 12, 6, 12, 6, 12, 6, 12, 6, 12}
                ) == 	"Solution does not exist"	);
    assert(A.condence({{1},{2},{0, 3},{1}}) == vi({0,0,0,0}));
    assert(A.possible(
                11, "GGGGGGGGGG", {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
                ) == "Solution exists"	);
    assert(A.possible(
                12, "GLLGGGLGLLGL", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0}, {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000}
                ) == "Solution exists"	);
    assert(A.possible(
                12, "GLLGGGLGLLGL", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0}, {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 999999999}
                ) == "Solution does not exist"	);
    assert(A.possible(
                34, "GGLGGGGLGGGGGGGGGGGLGGGGGGLGGGGGGLGGGGGGGGGGGGGGGGGGGLGGLGGGGGGLGGGGGGGLGGGLGGGGGGGGGGGGGLGGLGGGGGGGGGLLGGGGGGGLGGGGGGGGGGGLGGGG", {28, 33, 5, 29, 8, 21, 0, 2, 15, 13, 2, 7, 6, 17, 7, 6, 28, 1, 31, 0, 28, 2, 1, 2, 25, 9, 20, 3, 10, 17, 17, 20, 8, 12, 21, 16, 3, 21, 26, 26, 11, 18, 9, 5, 21, 9, 10, 31, 6, 27, 14, 31, 19, 28, 13, 18, 17, 13, 33, 28, 23, 30, 23, 4, 29, 8, 31, 14, 10, 5, 5, 1, 30, 10, 21, 21, 15, 7, 24, 1, 12, 6, 4, 8, 6, 12, 27, 24, 25, 31, 0, 28, 19, 21, 12, 4, 13, 18, 22, 10, 4, 5, 11, 4, 9, 23, 27, 33, 20, 20, 17, 33, 6, 11, 14, 32, 22, 9, 16, 18, 13, 13, 24, 28, 25, 10, 29, 3}, {0, 26, 26, 26, 19, 4, 11, 20, 14, 12, 18, 15, 31, 11, 18, 12, 13, 28, 1, 22, 11, 28, 15, 6, 9, 19, 23, 21, 22, 2, 14, 19, 33, 14, 6, 9, 25, 16, 20, 3, 31, 21, 32, 24, 12, 13, 21, 0, 1, 16, 30, 6, 31, 13, 2, 22, 33, 26, 27, 23, 29, 23, 8, 25, 16, 26, 23, 13, 17, 25, 16, 11, 13, 24, 13, 19, 30, 8, 2, 19, 21, 7, 26, 12, 1, 7, 21, 23, 10, 12, 2, 26, 9, 18, 14, 8, 27, 12, 16, 16, 1, 24, 31, 14, 32, 33, 22, 9, 6, 19, 19, 23, 7, 1, 28, 6, 30, 6, 31, 6, 16, 12, 20, 15, 14, 33, 7, 1}, {1, 2, 43562524, 2, 1, 1, 1, 15410815, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 390565277, 3, 1, 1, 1, 2, 1, 7303135, 1, 1, 1, 1, 1, 2, 258437555, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9060141, 1, 147505392, 29374056, 1, 1, 1, 1, 7, 1, 367937372, 2, 2, 7, 1, 1, 4, 2, 1, 1, 1, 1, 172593024, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 516116615, 1, 1, 149433774, 2, 1, 1, 1, 5, 1, 1, 1, 1, 250234173, 157275877, 1, 1, 1, 2, 1, 1, 1, 148431906, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 43619493, 1, 3, 2, 1}
                ) == "Solution does not exist"	);
    //assert(A.possible(
    //            ) == );
    return 0;
}
