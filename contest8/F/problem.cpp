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

#define DEBUG

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

int gcd(int x, int y) {
    while(x) {
        y%= x;
        swap(x, y);
    }
    return y;
}

struct Vector{
    int x, y;
    Vector(int x=0, int y=0): x(x), y(y) {n();};
    void n() {
        if (y == 0 && x == 0)
            return;
        int d = gcd(abs(x), abs(y));
        x /= d;
        y /= d;
    }
};

std::ostream& operator << (std::ostream& o, const Vector& v) {
    return o << "(" << v.x << ", " << v.y << ")";
}

bool clock(const Vector& a, const Vector& b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x > 0;
}

bool clockEQ(const Vector& a, const Vector& b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x >= 0;
}


bool A(const Vector& a) {
    //assert(!(a.y == 0 && a.x == 0));
    return a.y > 0 || (a.y == 0 && a.x > 0);
}

bool operator<(const Vector& a, const Vector& b) {
    if (A(a) == A(b))
        return clock(a, b);
    return (A(a) && !A(b));
}

bool operator==(const Vector& a, const Vector& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vector& a, const Vector& b) {
    return !(a == b);
}

vector<Vector> vecs;
int compress(const Vector& a) {
    int i = lower_bound(all(vecs), a) - vecs.begin();
    assert(a == vecs[i]);
    return i;
}

int findFirstNotLessP2(int n) {
    int x = 0;
    while ((1 << x) < n)
        ++x;
    return x;
}

int findFirstNotLessP4(int n) {
    int x = 0;
    while ((1 << (x+x)) < n)
        ++x;
    return x;
}

template<class T>
struct SparseTable {
    void init(const vector<T>& v) {
        int n = findFirstNotLessP4(v.size());
        ++n;
        data.resize(n);
        data.shrink_to_fit();
        data[0] = v;
        size_t items = data[0].size();
        for (int i = 1; i < n; ++i) {
            data[i] = data[i - 1];
            int add = (1 << (2 * (i - 1)));
            //data[i].resize(data[i].size() - add);
            //data[i].shrink_to_fit();
            for (int j = 0; j < data[i].size(); ++j) {
                if (j + add < data[i - 1].size()) {
                    data[i][j] = max(data[i][j], data[i - 1][j + add]);
                }
                if (j + 2 * add < data[i - 1].size()) {
                    data[i][j] = max(data[i][j], data[i - 1][j + 2 * add]);
                }
                if (j + 3 * add < data[i - 1].size()) {
                    data[i][j] = max(data[i][j], data[i - 1][j + 3 * add]);
                }
            }
            items += data[i].size();
        }
        //debug(data);
        // debug(items * sizeof(T));
        p4.resize(data[0].size() + 1);
        for (int i = 0; i < p4.size(); ++i) {
            int p = findFirstNotLessP4(i);
            if ((1 << (p+p)) > i)
                --p;
            p4[i] = p;
        }
        // debug(data.size() * data[0].size() * sizeof(T));
    }
    T req(int l, int r) const {
        int len = p4[r-l+1];
        T res = data[len][l];
        //debug(len);
        for (int i = 1; i < 4; ++i) {
            res = max(res, data[len][min(l + i * (1 << (len+len)), r - (1 << (len + len)) + 1)]);
        }
        return res;
    }
    void clear() {
        data.clear();
        data.shrink_to_fit();
    }
    vector<vector<T> > data;
    vector<int> p4;
};

struct RectangeData {
    Vector lower, upper;
    int index;
    void init(const vector<Vector>& a) {
        for (size_t i = 0; i < a.size(); ++i) {
            bool ok = 1;
            for (size_t j = 0; j < a.size(); ++j) {
                if (i == j)
                    continue;
                ok = ok && clockEQ(a[i], a[j]);
            }
            if (ok)
                lower = a[i];
        }
        for (size_t i = 0; i < a.size(); ++i) {
            bool ok = 1;
            for (size_t j = 0; j < a.size(); ++j) {
                if (i == j)
                    continue;
                ok = ok && !clock(a[i], a[j]);
            }
            if (ok)
                upper = a[i];
        }
        assert(lower != Vector() && upper != Vector());
    }
};

int findMinSteps(const vector<pii>& al, int C) {
    // first - vertex
    // second - dist
    int n = al.size();
    int p2 = findFirstNotLessP2(n);
    vector<vector<int> > howLong(p2 + 1, vector<int> (n, 0));
    vector<vector<int> > where(p2 + 1, vector<int> (n, 0));
    for (int i = 0; i < n; ++i) {
        where[0][i] = i;
        howLong[0][i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        howLong[0][i] = al[i].second;
        where[0][i] = al[i].first;
    }
    for (int j = 1; j <= p2; ++j) {
        for (int i = 0; i < n; ++i) {
            where[j][i] = where[j - 1][where[j - 1][i]];
            howLong[j][i] = min(1000000000, howLong[j - 1][i] + howLong[j - 1][where[j - 1][i]]);
        }
    }

    int res = 1e9;
    for (int v = 0; v < n; ++v) {
        int steps = 0;
        int minSteps = 1e9;
        int path = 0;
        int V = v;
        for (int i = p2; i >= 0; --i) {
            if (path + howLong[i][v] >= C) {
                minSteps = min(minSteps, (1 << i) + steps);
            } else {
                path += howLong[i][v];
                steps += 1 << i;
                v = where[i][v];
            }
        }
        v = V;
        // debug(v);
        // debug(minSteps);
        res = min(res, minSteps);
    }
    return res;
}

vector<Vector> getCorners(const vector<int>& x, const vector<int>& y) {
    vector<Vector> vs;
    for (size_t i = 0; i < x.size(); ++i) {
        for (size_t j = 0; j < y.size(); ++j) {
            vs.push_back(Vector(x[i], y[j]));
        }
    }
    return vs;
}

int rightEnd(const RectangeData& data) {
     const int LEN = vecs.size();
     const Vector& lower= data.lower;
     int add = 0;
     if (!A(lower))
        add = LEN;
     return add + compress(data.upper);
}

vector<int> fromStr(string s) {
    stringstream o;
    o << s;
    vector<int> x;
    int y;
    while(o >> y) {
        x.push_back(y);
    }
    return x;
}

int main () {
    if (0) {
        vector<int> a;
        for (int i = 0; i < 253; ++i)
            a.push_back(rand());
        debug(a);
        SparseTable<int> t;
        t.init(a);
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = i; j < a.size(); ++j) {
                int res = -1;
                for (size_t k = i; k <= j; ++k) {
                    res = max(res, a[k]);
                }
                debug(i);
                debug(j);
                debug(res);
                debug(t.req(i, j));
                assert(res == t.req(i, j));
            }
        }
        return 0;
    }
    if (0) {
        SparseTable<int> t;
        int x[] = {-3,-2,-1,-0,-1,-2,-3,-5, 1};
        vector<int> xv(x, x + sizeof(x)/sizeof(int));
        debug(xv);
        t.init(xv);
        debug(t.req(0, 6));
        debug(t.req(0, 2));
        debug(t.req(0, 4));
        debug(t.req(3, 4));
        debug(t.req(3, 5));
        debug(t.req(4, 5));
        debug(t.req(6,6));
        debug(t.req(6,7));
        debug(t.req(6,8));
        return 0;
    }
    if (0) {
        Vector v1(1, 0);
        Vector v2(0, -1);
        debug(clock(v1, v2));
    }
    if (0) {
        {
            vector<Vector> cs = getCorners(fromStr("-1 -2"), fromStr("-1 -2"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            vector<Vector> cs = getCorners(fromStr("1 2"), fromStr("1 2"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            //4 0 6 -4
            vector<Vector> cs = getCorners(fromStr("4 6"), fromStr("0 -4"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            vector<Vector> cs = getCorners(fromStr("2 4"), fromStr("0 2"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            vector<Vector> cs = getCorners(fromStr("-11 11"), fromStr("1 2"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            vector<Vector> cs = getCorners(fromStr("1 2"), fromStr("-11 11"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            vector<Vector> cs = getCorners(fromStr("-11 11"), fromStr("-2 -1"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
        {
            vector<Vector> cs = getCorners(fromStr("-2 -1"), fromStr("-11 11"));
            RectangeData data;
            data.init(cs);
            debug(data.lower.x);
            debug(data.lower.y);
            debug(data.upper.x);
            debug(data.upper.y);
        }
    }
    if (0) {
        if(0){
            vector<pii> al;
            al.push_back(pii(1,1));
            al.push_back(pii(2,1));
            al.push_back(pii(0,1));
            findMinSteps(al, 5);
        }
        if(0) {
            vector<pii> al;
            al.push_back(pii(1,1));
            al.push_back(pii(2,0));
            al.push_back(pii(0,1));
            findMinSteps(al, 1);
        }
        {
            vector<pii> al;
            al.push_back(pii(1,1));
            al.push_back(pii(2,1));
            al.push_back(pii(3,1));
            al.push_back(pii(4,1));
            al.push_back(pii(0,1));
            al.push_back(pii(6,100));
            al.push_back(pii(7,0));
            al.push_back(pii(0,0));
            al.push_back(pii(5,1));
            findMinSteps(al, 10);
        }
    }
//    return 0;

    //freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    //n = min(n, 33000);
    vector<vector<Vector> > corners;
    for (int i = 0; i < n; ++i) {
        vector<int> x(2);
        vector<int> y(2);
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        corners.push_back(getCorners(x,y));
    }

    vector<RectangeData> datas(n);
    for (int i = 0; i < n; ++i) {
        datas[i].index = i;
        datas[i].init(corners[i]);
    }
    for (int i = 0; i < n; ++i) {
        vecs.push_back(datas[i].lower);
        vecs.push_back(datas[i].upper);
    }

    sort(all(vecs)); vecs.erase(unique(all(vecs)), vecs.end());
    // debug(vecs);

    const int LEN = vecs.size();
    // first right
    // second index
    vector<pii> tableVector(LEN + LEN);
    for (size_t i = 0; i < datas.size(); ++i) {
        //debug(compress(datas[i].lower));
        tableVector[compress(datas[i].lower)] = pii(rightEnd(datas[i]), datas[i].index);
    }

    // first -- right pos
    // second - i
    set<pii> rightEnds;
    for (int i = 0; i < n; ++i) {
        rightEnds.insert(pii(compress(datas[i].upper), i));
        rightEnds.insert(pii(LEN + compress(datas[i].upper), i));
        rightEnds.insert(pii(2 * LEN + compress(datas[i].upper), i));
    }

    SparseTable<pii> table;
    table.init(tableVector);

    // clean rightEnds
    // debug(rightEnds);
    for (int i = 0; i < n; ++i) {
        int ll = compress(datas[i].lower);
        int rr = rightEnd(datas[i]);
        pii maxpii = table.req(ll, rr);
        maxpii.first %= LEN;
        //int RI = rightEnd(datas[i]) % LEN;

        set<pii>::iterator it = rightEnds.upper_bound(maxpii);
        // debug(i);
        int startIndex = it->second;
        auto itNext = it;
        ++itNext;
        while(itNext->second != startIndex) {
            ///debug(*it);
            itNext = it;
            ++itNext;
            if (clockEQ(datas[it->second].lower, datas[maxpii.second].upper) && clockEQ(datas[maxpii.second].upper, datas[it->second].upper)) {
                rightEnds.erase(it);
            } else {
                break;
            }
            it = itNext;
        }
    }
    //debug(rightEnds);
    //debug(rightEnds.size());

    // first - vertex
    // second - dist
    vector<pii> al(n, pii(-1,-1));
    for (int i = 0; i < n; ++i) {
        int ll = compress(datas[i].lower);
        int rr = rightEnd(datas[i]);
        //debug(ll);
        //debug(rr);
        pii maxpii = table.req(ll, rr);
        maxpii.first %= LEN;
        int RI = rightEnd(datas[i]) % LEN;

        set<pii>::iterator it = rightEnds.upper_bound(maxpii);
        // assert(!(clockEQ(datas[it->second].lower, datas[maxpii.second].upper) && clockEQ(datas[maxpii.second].upper, datas[it->second].upper)));
        int j = it->second;
        int RJ = it->first;
        int len = RJ - RI;
        if (len == 0)
            len = LEN;
        al[i] = pii(
                j, len
            );
    }
    /*debug(al[0]);
    debug(al[al[0].first]);
    debug(LEN);*/
    //debug(al);
    //debug('s');
    //assert(n == 7);
    table.clear();
    cout << findMinSteps(al, LEN) << "\n";

    return 0;
}
