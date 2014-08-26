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
const long long LLINF = std::numeric_limits<ll>::max() / 4;

bool test(const vector<vector<pii>>& al, int from, int to, int add, const vi& cheese) {
    int n = al.size();
    vector<ll> minWeight(n, LLINF);
    minWeight[from] = 1LL * add + 1LL * cheese[from];
    set<pair<ll, int> > Q;
    Q.insert(make_pair(minWeight[from], from));
    while(!Q.empty()) {
        int v = Q.begin()->second;
        if (v == to)
            break;
        Q.erase(Q.begin());
        ll curW = minWeight[v];
        for (int i = 0; i < al[v].size(); ++i) {
            int w = al[v][i].second;
            int v2 = al[v][i].first;
            if (curW > w)
                continue;
            ll newMinW = curW + cheese[v2];
            if (newMinW < minWeight[v2]) {
                Q.erase(make_pair(minWeight[v2], v2));
                minWeight[v2] = newMinW;
                Q.insert(make_pair(minWeight[v2], v2));
            }
        }
    }
    return minWeight[to] < LLINF;
}

int main() {
    int n, m, from, to;
    cin >> n >> m >> from >> to;
    --from;
    --to;
    vector<int> cheese(n);
    for (int i = 0; i < n; ++i) {
        cin >> cheese[i];
    }
    vector<vector<pii>> al(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        al[a].push_back(pii(b,c));
        al[b].push_back(pii(a,c));
    }
    int l = 0;
    int u = 1e9 + 1;
    while (l + 1 < u) {
        int m = (l + u) / 2;
        if (test(al, from, to, m, cheese))
            l = m;
        else
            u = m;
    }
    if (test(al, from, to, l, cheese)) {
        cout << l << "\n";
    } else {
        cout << "-1\n";
    }


    return 0;
}
