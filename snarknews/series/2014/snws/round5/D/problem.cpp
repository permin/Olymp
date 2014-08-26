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
#include <valarray>

using namespace std;

#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL_((0,__VA_ARGS__, 5,4,3,2,1))
#define VA_NUM_ARGS_IMPL_(tuple) VA_NUM_ARGS_IMPL tuple
#define VA_NUM_ARGS_IMPL(_0,_1,_2,_3,_4,_5,N,...) N

#define macro_dispatcher(macro, ...) macro_dispatcher_(macro, VA_NUM_ARGS(__VA_ARGS__))
#define macro_dispatcher_(macro, nargs) macro_dispatcher__(macro, nargs)
#define macro_dispatcher__(macro, nargs) macro_dispatcher___(macro, nargs)
#define macro_dispatcher___(macro, nargs) macro ## nargs

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
int MOD;

int add(int x,int y) {
    int r = x + y;
    if (r >= MOD)
        r -= MOD;
    return r;
}

ll add2(ll x,ll y) {
    ll r = x + y;
    if (r >= 123456789123456LL)
        r -= 123456789123456LL;
    return r;
}

class Fenwick {
public:
    explicit Fenwick(int n=0):n(n) {

    }
    void inc(int x, int a) {
        while (x < n) {
            data[x] = add(data[x], a);
            data_[x] = add2(data_[x], a);
            x |= x + 1;
        }
    }
    ll sumLL(int l) {
        ll r = 0;
        while(l >= 0) {
            r = add2(r, data_[l]);
            l = (l & (l + 1)) - 1;
        }
        return r;
    }
    int sum(int l) {
        int r = 0;
        while(l >= 0) {
            r = add(r, data[l]);
            l = (l & (l + 1)) - 1;
        }
        return r;
    }
    int sum(int l, int r) {
        if (l > r)
            return 0;
        return (sum(r) - (l? sum(l-1) : 0));
    }
    ll sumLL(int l, int r) {
        if (l > r)
            return 0;
        return (sumLL(r) - (l? sumLL(l-1) : 0));
    }
private:
    int n;
    map<int, int> data;
    map<int, ll> data_;
};

vector<int> compress(const vi& a) {
    vector<int> res(a.size(), -1);
    int id = 0;
    set<int> s(all(a));
    map<int, int> dict;
    for (int x: s) {
        dict[x] = id ;
        ++id;
    }
    for (int i = 0; i < res.size(); ++i)
        res[i] = dict[a[i]];
    return res;
}

int main() {
    int n;
    cin >> n >> MOD;
    vector<int> a(n);
    for (int i = 0; i < a.size(); ++i) {
        cin >> a[i];
    }
    debug(a);
    a = compress(a);
    debug(a);

    deque<Fenwick> len;
    len.push_back(Fenwick(n+1));
    len.back().inc(n, 1);
    len.push_back(Fenwick(n+1));
    len.back().inc(a.back(), 1);
    for (int i = n - 2; i >= 0; --i) {
        if (len.back().sumLL(a[i] + 1, n) != 0) {
            len.push_back(Fenwick(n+1));
        }
        len.back().inc(a[i], len.front().sum(a[i] + 1, n));
    }
    cout << len.back().sum(n - 1) << "\n";
    return 0;
}

