/* Team: moscow04 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <deque>
#include <queue>
#include <string>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>

#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

//#define DEBUG

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)((a).size()))
#define pb push_back
#define MP make_pair
#define mp MP

#ifdef DEBUG
    #define debug(x) cerr << #x << ": " << (x) << endl;
#else
    #define debug(x) ;
#endif

typedef pair<int, int> pii;
typedef long long ll;

template <typename T> T sqr (T x) {return x * x;}
template <typename T> T abs (T x) {return x > 0 ? x : -x;}

template <typename T>
ostream & operator << (ostream & out, vector<T> const & a) {
    out << "[";
    for (int i = 0; i < sz(a); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << a[i];
    }
    out << "]";
    return out;
}

template <typename T>
ostream & operator << (ostream & out, set<T> const & a) {
    out << "{";
    for (typename set<T>::iterator it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) {
            out << ", ";
        }
        out << *it;
    }
    out << "}";
    return out;
}


template <typename T1, typename T2>
ostream & operator << (ostream & out, pair<T1, T2> const & p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

void showTime () {
#ifdef DEBUG
    static double prev;
    static bool first = true;

    double curr = (double)clock() / CLOCKS_PER_SEC;

    cerr.setf(ios::fixed);
    cerr.precision(3);
    cerr << "<";
    if (!first) {
        cerr << curr - prev << "sec, ";
    }
    cerr << curr << "sec>\n";

    first = false;
    prev = curr;
#endif
}

class Fenwick {
public:
    explicit Fenwick(int n):
        data(n){}
    void inc(size_t i, int val) {
        for (;i < data.size(); i |= (i + 1))
            data[i] += val;
    }
    ll sum(int r) {
        ll res = 0;
        while(r >=0 ){
            res += data[r];
            r = r & (r + 1);
            --r;
        }
        return res;
    }
    ll sum(int l , int r) {
        ll res = sum(r);
        if (l)
            res -= sum(l - 1);
        return res;
    }
    vector<int> data;
};

struct SegmentTree {
    void init(vector<vector<int>>& a, int maxElement) {
        deleted.assign(maxElement+1, false);
        n = 1;
        while(n < int(a.size()))
            n *= 2;
        data.resize(n + n);
        for (size_t i = 0; i < a.size(); ++i) {
            data[n + i] = a[i];
            sort(all(data[n+i]));
        }
        debug(n);
        for (int  i = n - 1; i > 0; --i) {
            //data[i] = data[i + i];
            data[i].resize(data[i+i].size() + data[i+i+1].size());
            // data[i].insert(all(data[i+i+1]));
            std::merge(all(data[i + i]), all(data[i+i+1]), data[i].begin());
        }
    }
    void erase(int pos) {
        deleted[pos] = 1;
    }
    void get(int l, int r, int bound, vector<int>& res) {
        get(l, r, 0, n, 1, bound, res);
    }
    void get(int l, int r, int treeLeft, int treeRight, int id, int bound, vector<int>& res) {
        if (r <= treeLeft || l >= treeRight)
            return;
        if (l <= treeLeft && treeRight <= r) {
            while (!data[id].empty() && data[id].back() >= bound) {
                if (!deleted[data[id].back()])
                    res.push_back(data[id].back());
                deleted[data[id].back()] = true;
                data[id].pop_back();
            }
            return;
        }
        int treeMed = (treeLeft + treeRight) / 2;
        get(l ,r, treeLeft, treeMed, id + id, bound, res);
        get(l ,r, treeMed, treeRight, id + id+1, bound, res);
    }
    int n;
    vector<vector<int>> data;
    vector<bool> deleted;
};

const int BOUND = 1e6;
//const int BOUND = 1e3;

int main () {
    //cout << sizeof(set<int>);
    //return 0;
    //freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stderr);
    int n, q;
    cin >> n >> q;
    vector<int> iq(n);
    for (int i =0 ; i < n; ++i) {
        cin >> iq[i];
    }

    ll sum = 0;
    vector<int> c(n);

    {
        Fenwick f(BOUND + 1);
        for (int i = n-1; i >= 0; --i) {
            ll num = f.sum(iq[i]-1);//f.sum(iq[i], BOUND);
            c[i] = num;
            sum += num;

            f.inc(iq[i], 1);
        }
    }

    debug(c);
    debug(sum);

    vector<vector<int>> g(BOUND + 1);
    for (int i = 0; i < n; ++i) {
        g[iq[i]].push_back(i);
    }

    SegmentTree st;
    st.init(g, n);

    cout << sum << "\n";

    while(q-->0) {
        int p;
        cin >> p;
        --p;

        vector<int> res;
        debug(iq[p]+1);
        st.get(0, iq[p] + 1, p, res);
        debug(res);
#ifdef DEBUG
        for (int i = 0; i < st.data.size(); ++i) {
            if (st.data[i].empty())
                continue;
            cerr << "i = " << i << " "; debug(st.data[i]);
        }
#endif

        for (size_t i = 0; i < res.size(); ++i) {
            int x = res[i];
            st.erase(x);
            sum -= c[x];
            c[x] = 0;
        }

        debug(c);
        debug(sum);

        cout << sum << "\n";
    }


    return 0;
}
