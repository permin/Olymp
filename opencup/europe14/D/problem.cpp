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

const int MIN_LETTER = 1;
const int MAX_LETTER = 26;
const int SPECIAL_CHAR = 0;
const int QUESTION_MARK = 27;
const int CHARS = 28;

const int EQUAL = 0;
const int LESS = 1;

int am[CHARS][CHARS][CHARS][2][2][2][2];

int code(const string&s, int i ){
    if (i >= s.size())
        return SPECIAL_CHAR;
    if (s[i] == '?')
        return QUESTION_MARK;
    return s[i] - 'a' + 1;
}

const int MOD = 1000 * 1000 * 1000 + 9;

int mul(int x, int y) {
    ll res = 1LL * x * y;
    return res % MOD;
}

int sum(int x, int y) {
    int r = x + y;
    if (r >= MOD)
        r -= MOD;
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    for (int a = SPECIAL_CHAR; a <= MAX_LETTER; ++a) {
        for (int b = SPECIAL_CHAR; b <= MAX_LETTER; ++b) {
            for (int c = SPECIAL_CHAR; c <= MAX_LETTER; ++c) {
                for (int first = EQUAL; first <= LESS; ++first) {
                    for (int second = EQUAL; second <= LESS; ++second) {
                        if (first == EQUAL && a > b)
                            continue;
                        if (second == EQUAL && b > c)
                            continue;

                        am[a][b][c][first][second][first || (a < b)][second || (b < c)] += 1;

                        if (a != SPECIAL_CHAR)
                            am[QUESTION_MARK][b][c][first][second][first || (a < b)][second || (b < c)] += 1;
                        if (b != SPECIAL_CHAR)
                            am[a][QUESTION_MARK][c][first][second][first || (a < b)][second || (b < c)] += 1;
                        if (c != SPECIAL_CHAR)
                            am[a][b][QUESTION_MARK][first][second][first || (a < b)][second || (b < c)] += 1;

                        if (a != SPECIAL_CHAR && b != SPECIAL_CHAR)
                            am[QUESTION_MARK][QUESTION_MARK][c][first][second][first || (a < b)][second || (b < c)] += 1;
                        if (c != SPECIAL_CHAR && b != SPECIAL_CHAR)
                            am[a][QUESTION_MARK][QUESTION_MARK][first][second][first || (a < b)][second || (b < c)] += 1;
                        if (c != SPECIAL_CHAR && a != SPECIAL_CHAR)
                            am[QUESTION_MARK][b][QUESTION_MARK][first][second][first || (a < b)][second || (b < c)] += 1;

                        if (c != SPECIAL_CHAR && b != SPECIAL_CHAR && a != SPECIAL_CHAR)
                            am[QUESTION_MARK][QUESTION_MARK][QUESTION_MARK][first][second][first || (a < b)][second || (b < c)] += 1;
                    }
                }
            }
        }
    }

    //debug(am[QUESTION_MARK][QUESTION_MARK][QUESTION_MARK][EQUAL][EQUAL][EQUAL][EQUAL]);

    int t;
    cin >> t;
    while(t --> 0) {
        string x,y,z;
        cin >> x >> y >> z;
        int n = max(x.size(), max(y.size(), z.size()));
        vector<int> a(n, SPECIAL_CHAR);
        vector<int> b(n, SPECIAL_CHAR);
        vector<int> c(n, SPECIAL_CHAR);
        for (int i = 0; i < n; ++i) {
            a[i] = code(x, i);
            b[i] = code(y, i);
            c[i] = code(z, i);
        }
        vector<vector<int> > dp(2, vi(2,0));
        dp[EQUAL][EQUAL] = 1;
        for (int i = 0; i < n; ++i) {
            vii new_dp(2, vi(2,0));
            for (int first = 0; first < 2; ++first)
                for (int second = 0; second < 2; ++second)
                    for (int new_first = 0; new_first < 2; ++new_first)
                        for (int new_second = 0; new_second < 2; ++new_second) {
                            new_dp[new_first][new_second] = sum(
                                    new_dp[new_first][new_second],
                                    mul(
                                        am[a[i]][b[i]][c[i]][first][second][new_first][new_second],
                                        dp[first][second]));
                        }
            dp.swap(new_dp);
        }
        cout << dp[LESS][LESS] << "\n";
    }

    return 0;
}
