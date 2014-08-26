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

vector<pii> neighbours(int i, int j, int n, int m) {
    vector<pii> res;
 for (int dx = -1; dx <= +1; ++dx)
        for (int dy = -1; dy <= +1; ++dy)
            if (dx != 0 || dy != 0) {
                int ni = i + dx;
                int nj = j + dy;
                if (ni < 0 || nj < 0 || ni >= n || nj >= m)
                    continue;
                res.push_back(pii(ni, nj));
            }
    return res;
}

int visited(const vector<string>& s, int i, int j) {
    set<pii> was;
    queue<pii> q;
    q.push(pii(i,j));
    was.insert(pii(i,j));
    while(!q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        bool ok = 1;
        //debug(i);
        //debug(j);
        //debug( neighbours(i, j, s.size(), s[0].size()));
        for (auto ne: neighbours(i, j, s.size(), s[0].size())) {
            if (s[ne.first][ne.second] == '*')
                ok = false;
        }
        //debug(ok);
        if (ok) {
            for (auto ne: neighbours(i, j, s.size(), s[0].size())) {
                if (was.count(ne) == 0) {
                    was.insert(ne);
                    q.push(ne);
                }
            }
        }
    }
    return was.size();
}

void solve(int n, int m, int k) {
    int s = n * m;
    for (unsigned long long mask = 0; mask < (1<<s); ++mask) {
        if (__builtin_popcount(mask) == k) {
            vector<string> res(n, string(m, '?'));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    res[i][j] = ((mask >> (i * m + j)) & 1) ? '*' : '.';
                }
            }
             for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (res[i][j] == '.') {
                        if (n * m - k == visited(res, i, j)) {
                            res[i][j] = 'c';
                            for (int i = 0; i < n; ++i)
                                cout << res[i] << "\n";
                            return;
                        }
                    }
                }
             }
        }
    }
    cout << "Impossible\n";
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        cout << "Case #" << i + 1 << ":\n";
        solve(a,b,c);
    }
    return 0;
}

