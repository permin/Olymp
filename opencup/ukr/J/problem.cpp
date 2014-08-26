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

struct Fenwick {
    explicit Fenwick(int n):
        data_(n){}
    void inc(int i, int value) {
        while (i < data_.size()) {
            data_[i] += value;
            i |= i + 1;
        }
    }
    int sum(int l, int r) {
        if (l > r)
            return 0;
        int res = sum(r);
        if (l)
            res -= sum(l - 1);
        return res;
    }
    int sum(int r) {
        int res = 0;
        while (r >= 0) {
            res += data_[r];
            r = (r & (r + 1)) - 1;
        }
        return res;
    }
    vector<int> data_;
};

vector<int> compressed;

int compress(int n) {
    assert(binary_search(all(compressed), n));
    return std::distance(compressed.begin(), lower_bound(all(compressed), n));
}

const int mod = 1e9 + 7.5;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int main() {
    if (0) {
        Fenwick t(10);
        t.inc(5, 1);
        t.inc(7, 1);
        debug(t.sum(0, 5));
        debug(t.sum(0, 6));
        debug(t.sum(0, 7));
        debug(t.sum(5, 7));
        debug(t.sum(6, 7));
        debug(t.sum(7, 7));
        debug(t.sum(8, 9));
        debug(t.sum(0, 4));
        return 0;
    }
    int n;
    cin >> n;
    vector<int> in(n);
    vector<int> out(n);
    for (int i = 0; i < n; ++i) {
        cin >> out[i] >> in[i];
        compressed.push_back(in[i]);
        compressed.push_back(out[i]);
    }
    sort(all(compressed));
    compressed.erase(unique(all(compressed)), compressed.end());
    //debug(compressed);

    Fenwick tree(compressed.size() + 1);
    vector<pii> v(n);
    for (int i = 0; i < in.size(); ++i) {
        v[i] = pii(out[i], in[i]);
    }
    //debug(v);

    sort(v.rbegin(), v.rend());

    int res = 1;
    int inUse = 0;

    for (int i = 0; i < v.size(); ) {
        int numGreater = tree.sum(compress(v[i].first) + 1, compressed.size());
        //debug(numGreater);

        int bound = i + 1;
        while(bound < v.size() && v[i].first == v[bound].first)
            ++bound;

        if (numGreater > inUse) {
            int k = numGreater - inUse;
            int x = bound - i;
            if (x <= k) {
                for (int y = 0; y < x; ++y)
                    res = mul(res, k - y);
            } else {
                for (int y = 0; y < k; ++y)
                    res = mul(res, x - y);
            }
            //res = mul(res, numGreater - inUse);
            inUse += min(k, x);
        }
        while (i < bound) {
            tree.inc(compress(v[i].second), 1);
            ++i;
        }
    }
    cout << res << "\n";

    return 0;
}

