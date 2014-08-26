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

int mod;
int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int add(int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x;
}

vii mul(const vii& A, const vii& B) {
    vii C(A.size(), B[0].size());
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B[0].size(); ++j) {
            for (int k = 0; k < A[i].size(); ++k) {
                C[i][j] = add(C[i][j], mul(A[i][k], B[k][j]));
            }
        }
    }
    return C[i][j];
}

vii Id(int n) {
    vii r(n, vi(n));
    for (int i = 0; i < n; ++i)
        r[i][i] = 1;
    return r;
}

vii modPow(vii A, ll n) {
    vii R = id(A.size());
    while (n) {
        if (n & 1LL) {
            R = mul(R, A);
            --n;
        } else {
            A = mul(A, A);
            n /= 2LL;
        }
    }
    return R;
}

int modPow(int x, int n) {
    int r = 1;
    while (n) {
        if (n & 1) {
            r = mul(r, x);
            --n;
        } else {
            x = mul(x,x);
            n /= 2;
        }
    }
    return r;
}

int inv(int x) {
    return modPow(x, mod - 2);
}

int C[100][100];

int main() {
    {
        for (int n = 0; n <= 70; ++n) {
            for (int k = 0; k <= n; ++k) {
                C[n][k] = (n == 0 || n == k) ? 1 : add(C[n-1][k-1], C[n-1][k]);
            }
        }
    }
    int m;
    ll t, p;
    cin >> m >> t >> p;
    mod = p;
    int n = 1 << m;
    vector<int> e(n);
    for (int i = 0; i < n; ++i) {
        cin >> e[i];
    }
    vector<int> b(m + 1);
    for (int i = 0 ;i <= m; ++i)
        cin >> b[i];
    vii A(m + 1, vi(m + 1));
    for (int x = 0; x <= m; ++x) {
        for (int y = 0; y <= m; ++y) {
            for (int i = 0; i <= x && i <= y; ++i) {
                if (m - x >= y - i) {
                    A[x][y] = add(A[x][y], mul(b[y - i + x - i], mul(C[x][i], C[m-x][y - i])));
                }
            }
        }
    }
    vii An = modPow(An, t);
    vector<int> colef(m +1);
    for (int i = 0; i <= m; ++i) {
        colef[i] = mul(An[0][i], inv(C[m][i]));
    }


    return 0;
}

