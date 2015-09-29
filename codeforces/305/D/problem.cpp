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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

vector<vector<size_t>> solve(vector<set<int>>& al) {
    vector<vector<size_t>>  res;
    int n = (int) al.size();
    vector<bool> used(al.size());
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            stack<int> s;
            s.push(i);
            res.resize(res.size() + 1);
            while(!s.empty()) {
                int v = s.top();
                used[v] = 1;
                if (al[v].size() == 0) {
                    s.pop();
                    res.back().push_back(v);
                } else {
                    int v2 = *al[v].begin();
                    s.push(v2);
                    al[v].erase(v2);
                    al[v2].erase(v);
                }
            }
        }
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    std::map<int, int> xs;
    std::map<int, int> ys;

    std::map<int, int> rxs;
    std::map<int, int> rys;

    map<pii, int> rrr;

    for (int i = 0; i < n; ++i) {
        //x[i] = (rand()) % 10;
        //y[i] = (rand()) % 10;
        cin >> x[i] >> y[i];
        --x[i];
        --y[i];
        rrr[pii(x[i],y[i])] = i;
        if (xs.count(x[i]) == 0) {
            int id = (int)xs.size();
            xs[x[i]] = id;
            rxs[id] = x[i];
        }
        if (ys.count(y[i]) == 0) {
            int id = (int)ys.size();
            ys[y[i]] = id;
            rys[id] = y[i];
        }
    }
    debug(xs);
    debug(rxs);
    debug(ys);
    debug(rys);
    debug(rrr);

    vector<set<int>> al(xs.size() + ys.size() + 2);
    for (int i = 0; i < n; ++i) {
        int a = xs.at(x[i]);
        int b = ys.at(y[i]) + int(xs.size());
        al[a].insert(b);
        al[b].insert(a);
    }
    int S1 = int(xs.size() + ys.size());
    int S2 = int(xs.size() + ys.size() + 1);

    for (int i = 0; i < (int)al.size(); ++i) {
        if (i < S1 && (al[i].size() & 1)) {
            int S = -1;
            if (i < (int)xs.size())
                S = S1;
            else
                S = S2;
            al[S].insert(i);
            al[i].insert(S);
        }
    }
    if (al[S1].size() & 1) {
        al[S1].insert(S2);
        al[S2].insert(S1);
    }
    debug(al);
    vector<vector<size_t>> tour = solve(al);
    vector<pair<int, int>> blue;
    for (auto& line: tour) {
        debug(line);
        for (size_t i = 0; i + 1 < line.size(); ++i) {
            size_t j = i + 1;
            if (i & 1)
                continue;
            int a = (int)line[i];
            int b = (int)line[j];
            if (a == S1 || a == S2 || b == S1 || b == S2)
                continue;
            if (a < (int)xs.size()) {
                blue.emplace_back(rxs.at(a), rys.at(b - (int)xs.size()));
            } else {
                blue.emplace_back(rxs.at(b), rys.at(a - (int)xs.size()));
            }
        }
    }
        debug(blue);
    string ans(n, 'r');
    for (auto el: blue) {
        ans[rrr.at(el)] = 'b';
    }

    cout << ans << "\n";

    return 0;
}
