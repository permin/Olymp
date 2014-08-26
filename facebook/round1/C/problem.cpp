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
#include <valarray>

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

int solve(int x, int y, int id, viii& dp, const vector<string>& plan) {
    int &res = dp[x][y][id];
    if (res >= 0)
        return res;
    res = 0;
    if (x >= plan.size() || y >= plan[x].size() || plan[x][y] == '#') {
        return res;
    }
    res = max(res, 1 + solve(x + 1, y, id, dp, plan));
    res = max(res, 1 + solve(x, y + 1, id, dp, plan));
    if (id == 1) {
        return res;
    }
    if (y + 1 < plan[x].size()) {
        for (int i = x; i >= 0; --i) {
            if (plan[i][y + 1] == '#')
                break;
            res = max(res, 2 + x - i + solve(i, y + 2, 1, dp, plan));
        }
    }
    if (x + 1 < plan.size()) {
        for (int i = y; i >= 0; --i) {
            if (plan[x + 1][i] == '#')
                break;
            res = max(res, 2 + y - i + solve(x + 2, i, 1, dp, plan));
        }
    }
    return res;
}

void solveTest() {
    int n,m;
    cin >> n >> m;
    vector<string> plan(n, string(m, '?'));
    for (int i = 0; i < n; ++i)
        cin >> plan[i];
    viii dp(n + 1, vii(m + 1, vi(2, -1)));
    cout << solve(0, 0, 0, dp, plan);
}

int main() {
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        cout << "Case #"<<test+1<<": ";
        solveTest();
        cout << endl;
    }
    return 0;
}
