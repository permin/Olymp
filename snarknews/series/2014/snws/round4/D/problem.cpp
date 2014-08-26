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
const long long LLINF = std::numeric_limits<ll>::max() / 3;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> w(k);
    for (int i = 0; i < k; ++i)
        cin >> w[i];
    int C = 1e5;
    vector<ll> dp(C, LLINF);
    dp[0] = 0;
    vector<ll> dp2;
    do {
        dp2 = dp;
        for (int i = 0; i < C; ++i) {
            for (int j = 0; j < k; ++j) {
                int nw = i + w[j];
                if (nw >= C)
                    continue;
                dp2[nw] = min(dp2[nw], dp[i] + 1);
            }
        }
    } while (dp2 != dp);
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        ll res = LLINF;
        if (x < C) {
            res = dp2[x];
        } else {
            for (int j = 0; j < k; ++j) {
                ll cc = (x - C + w[j] - 1) / w[j];
                res = min(res, cc + dp2[(x - cc * w[j])]);
            }
        }
        if (res >= LLINF)
            cout << "-1";
        else
            cout << res;
        cout << "\n";
    }


    return 0;
}
