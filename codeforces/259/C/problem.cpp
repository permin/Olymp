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

vector<int> current;
vector<int> should;
vector<int> path;
int root;

void dfs(int v, int p, const vii& al, vector<bool>& used) {
    path.push_back(v);
    current[v] ^= 1;
    used[v] = 1;
    for (int v2: al[v]) {
        if (v2 == p)
            continue;
        if (used[v2])
            continue;
        dfs(v2, v, al, used);
        path.push_back(v);
        current[v] ^= 1;
    }
    if (current[v] != should[v]) {
        if (p != -1) {
            path.push_back(p);
            path.push_back(v);
            current[v] ^= 1;
            current[p] ^= 1;
        } else {
            // root
            assert(!path.empty() && path.back() == v);
            path.pop_back();
            current[v] ^= 1;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vii al(n);
    for (int i = 0; i < m; ++i) {
        int a,b;
        cin >> a >> b;
        --a;--b;
        al[a].push_back(b);
        al[b].push_back(a);
    }
    should.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> should[i];
    }
    current.assign(n, 0);
    int st = -1;
    for (int i = 0; i < n; ++i) {
        if (should[i] == 1) {
            st = i;
        }
    }
    if (st == -1) {
        cout <<  "0\n";
        return 0;
    }
    root = st;
    vector<bool> used(n);
    dfs(st, -1, al, used);
    if (should == current) {
        cout << path.size() << "\n";
        for (int x: path) {
            cout << x + 1 << " ";
        }
        cout << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}

