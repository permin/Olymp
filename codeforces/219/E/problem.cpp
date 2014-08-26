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

bool solved;

vii t(const vii& a) {
    vii b(a[0].size(), vi(a.size(), -1));
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < a[i].size(); ++j) {
            b[j][i] = a[i][j];
        }
    return b;
}

bool tryColor(const vii& a, const vi& c, vii& b) {
    b = a;
    for (int ii = 0; ii < a.size(); ii += 2) {
        int c11,c12,c22,c21;
        c11 = -1; c12 = -1; c21 = -1; c22 = -1;
        for (int di = 0; di < 2; ++di) {
            int i = ii + di;
            if (i == a.size())
                break;
            for (int j = 0; j < a[i].size(); ++j) {
                int *cc = 0;
                if (i & 1) {
                    if (j & 1)
                        cc = &c22;
                    else
                        cc = &c21;
                } else {
                    if (j & 1)
                        cc = &c12;
                    else
                        cc = &c11;
                }
                if (a[i][j] == 0)
                    continue;;
                if (*cc == -1) {
                    *cc = a[i][j];
                }
                if (*cc != a[i][j])
                    return 0;
            }
        }
        if (c11 != -1 && c11 != c[0] && c11 != c[1])
            return 0;
        if (c12 != -1 && c12 != c[0] && c12 != c[1])
            return 0;
        if (c21 != -1 && c21 != c[2] && c21 != c[3])
            return 0;
        if (c22 != -1 && c22 != c[2] && c22 != c[3])
            return 0;
        if (c11 == -1 && c12 == -1) {
            c11 = c[0];
            c12 = c[1];
        } else if (c11 == c12) {
            return 0;
        } else if (c12 == -1) {
            c12 = c11 ^ c[0] ^ c[1];
        } else if (c11 == -1) {
            c11 = c12 ^ c[0] ^ c[1];
        }
        if (c21 == -1 && c22 == -1) {
            c21 = c[2];
            c22 = c[3];
        } else if (c21 == c22) {
            return 0;
        } else if (c22 == -1) {
            c22 = c21 ^ c[2] ^ c[3];
        } else if (c21 == -1) {
            c21 = c22 ^ c[2] ^ c[3];
        }
        for (int di = 0; di < 2; ++di) {
            int i = ii + di;
            if (i == a.size())
                break;
            for (int j = 0; j < a[i].size(); ++j) {
                if (i & 1) {
                    if (j & 1)
                        b[i][j] = c22;
                    else
                        b[i][j] = c21;
                } else {
                    if (j & 1)
                        b[i][j] = c12;
                    else
                        b[i][j] = c11;
                }
            }
        }
    }
    return 1;
}

void out(const vii& a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            cout << a[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int n,m;
    cin >> n>> m;
    vii a(n,vi(m, -1));
    for (int i =0 ; i < n; ++i)  {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            a[i][j] = s[j] - '0';
        }
    }
    vi colors{1,2,3,4};
    vii b;
    vii ta = t(a);
    do {
        if (tryColor(a, colors, b)) {
            out(b);
            return 0;
        }
        if (tryColor(ta, colors, b)) {
            out(t(b));
            return 0;
        }
    } while (next_permutation(all(colors)));
    cout << 0 << "\n";

    return 0;
}

