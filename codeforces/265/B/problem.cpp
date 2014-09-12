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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

vector<vi> coord;

vector<int> a;

bool eq(vi x, vi y) {
    sort(all(x));
    sort(all(y));
    return x == y;
}

vi add(vi x, const vi& y) {
    for (int i = 0; i < 3; ++i)
        x[i] += y[i];
    return x;
}
vi sub(vi x, const vi& y) {
    for (int i = 0; i < 3; ++i)
        x[i] -= y[i];
    return x;
}

bool zero(const vi& x) {
    for (int i = 0; i < x.size(); ++i)
        if (x[i])
            return 0;
    return 1;
}

ll scal(const vi& x, const vi& y) {
    ll res = 0;
    for (int i = 0; i < 3; ++i) {
        res += 1LL * x[i] * y[i];
    }
    return res;
}

ll len(const vi& x) {
    return scal(x, x);
}


void doit() {
    if (a.size() == 4) {
        vector<bool> others(8);
        for (int i = 0; i < 8; ++i) {
            if (std::count(all(a), i) == 1) {
                sort(all(coord[i]));
            } else {
                others[i] = 1;
            }
        }
        vii res(8);
        do {
            do {
                do {
                    do {
                        vii points;
                        vi dx = sub(coord[a[1]], coord[a[0]]);
                        vi dy = sub(coord[a[2]], coord[a[0]]);
                        vi dz = sub(coord[a[3]], coord[a[0]]);
                        vi O = coord[a[0]];
                        ll le = len(dx);
                        if (le == 0 || len(dy) != le || len(dz) != le)
                            goto outer;
                        if (scal(dx, dy) || scal(dy, dz) || scal(dz, dx))
                            goto outer;
                        points.push_back(add(O, add(dx, dy)));
                        points.push_back(add(O, add(dx, dz)));
                        points.push_back(add(O, add(dz, dy)));
                        points.push_back(add(O, add(dx, add(dy, dz))));
                        for (int i = 0; i < 4; ++i) {
                            bool ok = 0;
                            for (int j = 0; j < 8; ++j) {
                                if (others[j]) {
                                    if (eq(coord[j], points[i])) {
                                        res[j] = points[i];
                                        ok = 1;
                                        others[j] = 0;
                                        break;
                                    }
                                }
                            }
                            if (!ok)
                                goto outer;
                        }
                        res[a[0]] = coord[a[0]];
                        res[a[1]] = coord[a[1]];
                        res[a[2]] = coord[a[2]];
                        res[a[3]] = coord[a[3]];
                        cout << "YES\n";
                        for (int i = 0; i < 8; ++i) {
                            cout << res[i][0] << " ";
                            cout << res[i][1] << " ";
                            cout << res[i][2] << "\n";
                        }
                        exit(0);
outer:;
                    } while (next_permutation(all(coord[a[3]])));
                } while (next_permutation(all(coord[a[2]])));
            } while (next_permutation(all(coord[a[1]])));
        } while(next_permutation(all(coord[a[0]])));
        return;
    }
    int m = 0;
    if (!a.empty())
        m = a.back() + 1;
    for (int i = m; i < 8; ++i) {
        a.push_back(i);
        doit();
        a.pop_back();
    }
}

int main() {
    for (int i = 0; i < 8; ++i) {
        vector<int> c(3);
        cin >> c[0] >> c[1] >> c[2];
        sort(all(c));
        coord.push_back(c);
    }
    doit();
    cout << "NO\n";

    return 0;
}
