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

const int MAX = 100*1000;
const int MAX2 = 1 << 17;

class Tree {
public:
    Tree():
        data(MAX2 * 2) {
        }
    void set(int pos, int val) {
        set(0, MAX2, pos, 1, val);
    }
    int max(int left, int right) {
        ++right;
        return max(left, right, 0, MAX2, 1);
    }
private:

    int max(int left, int right, int tree_left, int tree_right, int id) {
        if (left <= tree_left && tree_right <= right) {
            return data[id];
        }
        if (right <= tree_left ||
                left >= tree_right) {
            return -1;
        }
        int med = (tree_right + tree_left) / 2;
        return std::max(
                max(left, right, tree_left, med, id + id),
                max(left, right, med, tree_right, id + id + 1));
    }

    void set(int left, int right, int pos, int id, int val) {
        if (left == pos && pos + 1 == right) {
            data[id] = val;
            return;
        }
        int med = (right + left) / 2;
        if (pos < med) {
            set(left, med, pos, id * 2, val);
        } else {
            set(med, right, pos, id * 2 + 1, val);
        }
        data[id] = std::max(data[id*2+1], data[id*2]);
    }

    vi data;
};


void solve(vector<pii> rocks, const vector<pii> dx, const vector<pii> dy, vector<bool>& res) {
    debug(rocks);
    debug(dx);
    debug(dy);
    vi p;
    {
        for (int i = 0; i < dx.size(); ++i) {
            p.push_back(i);
        }
        sort(all(p), [&](int i, int j) {
            return make_pair(dx[i], dy[i]) < make_pair(dx[j], dy[j]);
        });
    }
    vector<deque<int>> rocks_by_y(MAX);
    for (const pii& ro: rocks) {
        rocks_by_y[ro.second].push_back(ro.first);
    }
    Tree tree;
    for (int i = 0; i < MAX; ++i) {
        sort(all(rocks_by_y[i]));
        rocks_by_y[i].push_back(INF);
        tree.set(i, rocks_by_y[i].front());
    }
    sort(all(rocks));
    int pos = 0;

    for (int i: p) {
        while (pos < rocks.size() && rocks[pos].first < dx[i].first) {
            int y = rocks[pos].second;

            rocks_by_y[y].pop_front();
            tree.set(y, rocks_by_y[y].front());
            ++pos;
        }
        int ans = tree.max(dy[i].first, dy[i].second);
        if (ans <= dx[i].second) {
            res[i] = true;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n,m,k,q;
    cin >> n >> m >> k >> q;
    vector<pii> rocks(k);
    for (int i = 0; i < k; ++i) {
        cin >> rocks[i].first >> rocks[i].second;
        --rocks[i].first;
        --rocks[i].second;
    }

    vector<pii> dx(q);
    vector<pii> dy(q);
    for (int i = 0; i < q; ++i) {
        cin >> dx[i].first >> dy[i].first >> dx[i].second >> dy[i].second;
        --dx[i].first;
        --dx[i].second;
        --dy[i].first;
        --dy[i].second;
    }

    vector<bool> ans(q, false);
    solve(rocks, dx, dy, ans);
    vector<pii> rocks2(rocks);
    for (int i = 0; i < rocks.size(); ++i) {
        swap(rocks2[i].first, rocks2[i].second);
    }
    solve(rocks2, dy, dx, ans);
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i])
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
