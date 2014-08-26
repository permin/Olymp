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
#include <unordered_map>
#include <functional>
#include <bitset>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

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
    std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,6);
int dice_roll = distribution(generator);  // generates number in the range 1..6
debug(dice_roll);
return 0;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int tests;
    cin >> tests;
    while(tests-->0) {
        int n, B, P;
        cin >> n >> B >> P;
        vector<int> v(n);
        vector<int> b(n);
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i] >> b [i] >> p[i];
        }
        vii dp(B + 1, vi(P + 1, 0));
        for (int i = 0; i < n; ++i) {
            vii ndp(dp);
            for (int bb = 0; bb <= B; ++bb) {
                for (int pp = 0; pp <= P; ++pp) {
                    int nbb = bb + b[i];
                    int npp = pp + p[i];
                    if (nbb > B || npp > P)
                        continue;
                    ndp[nbb][npp] = max(ndp[nbb][npp], dp[bb][pp] + v[i]);
                }
            }
            ndp.swap(dp);
        }
        int res = 0;
        for (int bb = 0; bb <= B; ++bb) {
            for (int pp = 0; pp <= P; ++pp) {
                res = max(res, dp[bb][pp]);
            }
        }
        cout << res << "\n";
    }

    return 0;
}
