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

vi inv(const vi& a) {
    vi b(a.size());
    for (int i = 0; i < a.size(); ++i)
        b[a[i]] = i;
    return b;
}

std::bitset<size_t(1000*1000*1000)*10> s;

int main() {

    std::ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    while(tests --> 0) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
            --p[i];
        }
        //debug(p);
        /*int k = 0;
        do {
            ++k;
            vector<bool> used(n);
            vector<size_t> a(n);
            for (int i = 0; i < n; ++i) {
                a[i] = i;
            }
            vector<int> pos(n);
            for (int i = 0; i < n; ++i) {
                pos[p[i]] = i;
            }

            for (int i = 0; i < n; ++i) {
                int x = pos[i];
                if (used[p[x]] || used[p[p[x]]]|| pos[i] == i)
                    continue;
                used[p[x]] = used[p[p[x]]] = true;
                a[p[x]] = p[p[x]];
                a[p[p[x]]] = p[x];
                swap(p[x], p[p[x]]);
            }
            vector<size_t> ai(n);
            for (int i = 0; i < n; ++i)
                ai[a[i]] = i;
            ans.push_back(ai);
            //debug(p);
        } while(!is_sorted(all(p)));*/

        vii cycles;
        vi used(n);
        vi por(p);
        for (int i = 0; i < n; ++i) {
            if (used[i])
                continue;
            int v = i;
            cycles.resize(cycles.size() + 1);
            while(!used[v]) {
                cycles.back().push_back(v);
                used[v] = 1;
                v = p[v];
            }
        }
        debug(cycles);

        int maxC = 0;
        for (int i = 0; i < cycles.size(); ++i) {
            maxC = max(maxC, int(cycles[i].size()));
        }
        if (maxC == 1) {
            cout << "0\n";
            continue;
        }
        if (maxC <= 2) {
            cout << 1 << "\n";
            for (int i: p)
                cout << i + 1 << " ";
            continue;
        }
        vector<vector<int>> ans;

        {
            vi a(n);
            for (int i = 0; i < n; ++i)
                a[i] = i;
            for (int i = 0; i < cycles.size(); ++i) {
                if (cycles[i].size() == 1)
                    continue;
                int b = 1;
                int e = int(cycles[i].size()) - 1;
                while(b < e) {
                    a[p[cycles[i][b]]] =  p[cycles[i][e]];
                    a[p[cycles[i][e]]] =  p[cycles[i][b]];
                    swap(p[cycles[i][b]], p[cycles[i][e]]);
                    ++b;
                    --e;
                }
            }
            ans.push_back(a);
        }
        {
            vi a(n);
            for (int i = 0; i < n; ++i)
                a[i] = i;
            for (int i = 0; i < cycles.size(); ++i) {
                if (cycles[i].size() == 1)
                    continue;
                    a[p[cycles[i][0]]] =  p[cycles[i][1]];
                    a[p[cycles[i][1]]] =  p[cycles[i][0]];
                    swap(p[cycles[i][0]], p[cycles[i][1]]);
                int b = 2;
                int e = int(cycles[i].size()) - 1;
                while(b < e) {
                    a[p[cycles[i][b]]] =  p[cycles[i][e]];
                    a[p[cycles[i][e]]] =  p[cycles[i][b]];
                    swap(p[cycles[i][b]], p[cycles[i][e]]);
                    ++b;
                    --e;
                }
            }
            ans.push_back(a);
        }

        debug(p);
        assert(is_sorted(all(p)));

        //swap(ans[0], ans[1]);
        cout << ans.size() << "\n";
        for (auto x: ans) {
            x = inv(x);
            for (size_t y: x) {
                cout << y + 1 << " ";
            }
            cout << "\n";
        }

        vi a = inv(ans[0]);
        vi b = inv(ans[1]);
        swap(a,b);

        vi c(n, -1);
        for (int i = 0; i < n; ++i)
            c[a[b[i]]] = i;
        debug(c);
        assert(c == por);

        //std::cerr << "solved!\n";
    }
    return 0;
}
