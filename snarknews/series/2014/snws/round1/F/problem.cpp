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

bool st(int x, int b) {
    vector<int> d;
    while(x) {
        d.push_back(x%b);
        x/=b;
    }
    bool ok = 1;
    for (int i = 0; i < d.size(); ++i) {
       if (d[i] != d[d.size() - 1 - i])
           ok = 0;
    }
    return ok;
}

int main() {
    int x;
    cin >> x;
    int res = 0;
    if (0) {
        int cor = 0;
        for (int b = 2; b < x; ++b)
            cor += st(x, b);
        debug(cor);
    }
    vector<int> ans;
    for (int b = 2; b * b <= x; ++b) {
        if (st(x, b))
            ans.push_back(b);
        res += st(x, b);
    }
    vector<int> f;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            f.push_back(i);
            f.push_back(x / i);
        }
    }
    sort(all(f));
    f.erase(unique(all(f)), f.end());
    for (int i= 0; i < f.size(); ++i) {
        int y = f[i] - 1;
        if (y >= 2 && x / (y + 1) < y) {
            ans.push_back(y);
            assert(x % y == (x / y));
            ++res;
        }
    }
    sort(all(ans));
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
