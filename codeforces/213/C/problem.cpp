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

vector<int> p;

void go(int cur, int num, int C, set<int,greater<int>>& s) {
    if (cur < 0)
        return;
    if (cur > C)
        return ;
    if (num == 0) {
        s.insert(cur);
        return;
    }
    int pc = 1;
    for (int i = 0; i < 100; ++i) {
        go(cur * pc, num - 1, C, s);
        pc *= p[num - 1];
        if (cur * pc > C)
            break;
    }
}

vector<int> solve(int num, int k) {
    set<int, greater<int>> s;
    go(1, num, 2 * k * k, s);
    vector<int> res(all(s));
    if (int(res.size()) < k) {
        return vector<int>();
    }
    random_shuffle(all(res));
    vector<int> stat(num);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < num; ++j) {
            if (res[i] % p[j] == 0)
                ++stat[j];
        }
    }
    for (int i = 0; i < num; ++i) {
        if (stat[i] * 2 < k)
            return vector<int>();
    }
    debug(stat);
    return res;
}


int main() {
    int n = 2;
    while (p.size() < 20) {
        bool ok = 1;
        for (int i = 2; i < n; ++i) {
            if (n % i == 0)
                ok = 0;
        }
        if (ok) {
            p.push_back(n);
        }
        ++n;
    }
    debug(p);
    //cin >> n;
    /*int p2 = 0;
    while ((1 << p2) < n)
        ++p2;
    debug(p2);

    for (int i = 0; i < n; ++i) {
        int x = 1;
        for (int j = 0; j < p2; ++j) {
            if ((i >> j) & 1)
                continue;
            x *= p[j];
        }
        debug(x);
        debug(2 * n * n);
        assert(x <= 2 * n * n);
        cout << x << " ";
    }*/

    int k;
    cin >> k;
    vector<int> res;
    int num = 0;
    while (1) {
        ++num;
        debug(num);
        res = solve(num, k);
        if (res.size()) {
            assert(int(res.size()) >= k);
            for (int i = 0; i < k; ++i) {
                cout << res[i] << " ";
            }
            cout << "\n";
            return 0;
        }
    }

    return 0;
}
