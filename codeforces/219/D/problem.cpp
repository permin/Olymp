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

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

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

vi dx, dy;

bool in(int i, int j, const  vector<vector<bool>>& am) {
    return i >= 0 && j >= 0 && i < am.size() && j < am[i].size();
}

int get(int i, int j, int d, viii& dp, const  vector<vector<bool>>& am) {
    int &res = dp[d][i][j];
    if (res >= 0)
        return res;
    res = am[i][j];
    if (res == 0)
        return res;
    int ni = i + dx[d];
    int nj = j + dy[d];
    if (in(ni,nj, am))
        res += get(ni, nj, d, dp, am);
    return res;
}

int main() {
    {
        for (int i = -1; i < 2; ++i){
            for (int j = -1; j < 2; ++j) {
                if (i == 0 && j == 0)
                    continue;
                dx.push_back(-i);
                dy.push_back(j);
            }
        }
        //debug(dx);
        //debug(dy);
    }
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> am(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i)  {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            am[i][j] = s[j] == '0';
        }
    }
    viii dp(8, vii(n, vi(m, -1)));

    int res = 0;
    vector<int> turn90(8);
    turn90[0] = 2;
    turn90[2] = 7;
    turn90[7] = 5;
    turn90[5] = 0;
    turn90[1] = 4;
    turn90[4] = 6;
    turn90[6] = 3;
    turn90[3] = 1;
    vi turn45(8);
    turn45[0] = 4;
    turn45[2] = 6;
    turn45[7] = 3;
    turn45[5] = 1;
    turn45[1] = 7;
    turn45[4] = 5;
    turn45[6] = 0;
    turn45[3] = 2;
    {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int d: {0,2,5,7}) {
                    int sz = get(i, j, d, dp, am);;
                    sz = min(sz, get(i,j,turn90[d], dp, am));
                    for (int s = 1; s < sz; ++s) {
                        int x = i + s * dx[d];
                        int y = j + s * dy[d];
                        if (get(x,y,turn45[d], dp, am) >= 2 * s + 1) {
                            ++res;
                        }
                    }
                }
            }
        }
    }
    debug(res);
    {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int d: {1,4,6,3}) {
                    int sz = get(i, j, d, dp, am);;
                    sz = min(sz, get(i,j,turn90[d], dp, am));
                    for (int s = 1; s < sz; ++s) {
                        int x = i + s * dx[d];
                        int y = j + s * dy[d];
                        if (get(x,y,turn45[d], dp, am) >= s + 1) {
                            ++res;
                            //debug(i);
                            //debug(j);
                            //debug(d);
                            //debug(s);
                        }
                    }
                }
            }
        }
    }
    cout << res << "\n";
    debug(1.0 * clock() / CLOCKS_PER_SEC);

    return 0;
}

